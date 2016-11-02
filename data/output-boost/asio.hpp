
  explicit async_result(Handler&)
  {
  }

  type get()
  {
  }

  explicit async_result_init(BOOST_ASIO_MOVE_ARG(Handler) orig_handler)
    : handler(BOOST_ASIO_MOVE_CAST(Handler)(orig_handler)),
      result(handler)
  {
  }

inline std::size_t adapt_completion_condition_result(bool result)
{
  return result ? 0 : default_max_transfer_size;
}


  template <typename Error>
  std::size_t operator()(const Error& err, std::size_t)
  {
    return !!err ? 0 : default_max_transfer_size;
  }


  explicit transfer_at_least_t(std::size_t minimum)
    : minimum_(minimum)
  {
  }


  template <typename Error>
  std::size_t operator()(const Error& err, std::size_t bytes_transferred)
  {
    return (!!err || bytes_transferred >= minimum_)
      ? 0 : default_max_transfer_size;
  }


  explicit transfer_exactly_t(std::size_t size)
    : size_(size)
  {
  }


  template <typename Error>
  std::size_t operator()(const Error& err, std::size_t bytes_transferred)
  {
    return (!!err || bytes_transferred >= size_) ? 0 :
      (size_ - bytes_transferred < default_max_transfer_size
        ? size_ - bytes_transferred : std::size_t(default_max_transfer_size));
  }

inline detail::transfer_all_t transfer_all()
{
  return detail::transfer_all_t();
}

inline detail::transfer_at_least_t transfer_at_least(std::size_t minimum)
{
  return detail::transfer_at_least_t(minimum);
}

inline detail::transfer_exactly_t transfer_exactly(std::size_t size)
{
  return detail::transfer_exactly_t(size);
}

  ~socket_base()
  {
  }

  explicit seq_packet_socket_service(boost::asio::io_service& io_service)
    : boost::asio::detail::service_base<
        seq_packet_socket_service<Protocol> >(io_service),
      service_impl_(io_service)
  {
  }

  void construct(implementation_type& impl)
  {
    service_impl_.construct(impl);
  }

  void destroy(implementation_type& impl)
  {
    service_impl_.destroy(impl);
  }

  boost::system::error_code open(implementation_type& impl,
      const protocol_type& protocol, boost::system::error_code& ec)
  {
    if (protocol.type() == SOCK_SEQPACKET)
      service_impl_.open(impl, protocol, ec);
    else
      ec = boost::asio::error::invalid_argument;
    return ec;
  }

  boost::system::error_code assign(implementation_type& impl,
      const protocol_type& protocol, const native_handle_type& native_socket,
      boost::system::error_code& ec)
  {
    return service_impl_.assign(impl, protocol, native_socket, ec);
  }

  bool is_open(const implementation_type& impl) const
  {
    return service_impl_.is_open(impl);
  }

  boost::system::error_code close(implementation_type& impl,
      boost::system::error_code& ec)
  {
    return service_impl_.close(impl, ec);
  }

  native_type native(implementation_type& impl)
  {
    return service_impl_.native_handle(impl);
  }

  native_handle_type native_handle(implementation_type& impl)
  {
    return service_impl_.native_handle(impl);
  }

  boost::system::error_code cancel(implementation_type& impl,
      boost::system::error_code& ec)
  {
    return service_impl_.cancel(impl, ec);
  }

  bool at_mark(const implementation_type& impl,
      boost::system::error_code& ec) const
  {
    return service_impl_.at_mark(impl, ec);
  }

  std::size_t available(const implementation_type& impl,
      boost::system::error_code& ec) const
  {
    return service_impl_.available(impl, ec);
  }

  boost::system::error_code bind(implementation_type& impl,
      const endpoint_type& endpoint, boost::system::error_code& ec)
  {
    return service_impl_.bind(impl, endpoint, ec);
  }

  boost::system::error_code connect(implementation_type& impl,
      const endpoint_type& peer_endpoint, boost::system::error_code& ec)
  {
    return service_impl_.connect(impl, peer_endpoint, ec);
  }

  explicit socket_acceptor_service(boost::asio::io_service& io_service)
    : boost::asio::detail::service_base<
        socket_acceptor_service<Protocol> >(io_service),
      service_impl_(io_service)
  {
  }

  void construct(implementation_type& impl)
  {
    service_impl_.construct(impl);
  }

  void destroy(implementation_type& impl)
  {
    service_impl_.destroy(impl);
  }

  boost::system::error_code open(implementation_type& impl,
      const protocol_type& protocol, boost::system::error_code& ec)
  {
    return service_impl_.open(impl, protocol, ec);
  }

  boost::system::error_code assign(implementation_type& impl,
      const protocol_type& protocol, const native_handle_type& native_acceptor,
      boost::system::error_code& ec)
  {
    return service_impl_.assign(impl, protocol, native_acceptor, ec);
  }

  bool is_open(const implementation_type& impl) const
  {
    return service_impl_.is_open(impl);
  }

  boost::system::error_code cancel(implementation_type& impl,
      boost::system::error_code& ec)
  {
    return service_impl_.cancel(impl, ec);
  }

  boost::system::error_code bind(implementation_type& impl,
      const endpoint_type& endpoint, boost::system::error_code& ec)
  {
    return service_impl_.bind(impl, endpoint, ec);
  }

  boost::system::error_code listen(implementation_type& impl, int backlog,
      boost::system::error_code& ec)
  {
    return service_impl_.listen(impl, backlog, ec);
  }

  boost::system::error_code close(implementation_type& impl,
      boost::system::error_code& ec)
  {
    return service_impl_.close(impl, ec);
  }

  native_type native(implementation_type& impl)
  {
    return service_impl_.native_handle(impl);
  }

  native_handle_type native_handle(implementation_type& impl)
  {
    return service_impl_.native_handle(impl);
  }

  template <typename SettableSocketOption>
  boost::system::error_code set_option(implementation_type& impl,
      const SettableSocketOption& option, boost::system::error_code& ec)
  {
    return service_impl_.set_option(impl, option, ec);
  }

  template <typename GettableSocketOption>
  boost::system::error_code get_option(const implementation_type& impl,
      GettableSocketOption& option, boost::system::error_code& ec) const
  {
    return service_impl_.get_option(impl, option, ec);
  }

  template <typename IoControlCommand>
  boost::system::error_code io_control(implementation_type& impl,
      IoControlCommand& command, boost::system::error_code& ec)
  {
    return service_impl_.io_control(impl, command, ec);
  }

  bool non_blocking(const implementation_type& impl) const
  {
    return service_impl_.non_blocking(impl);
  }

  bool native_non_blocking(const implementation_type& impl) const
  {
    return service_impl_.native_non_blocking(impl);
  }

  endpoint_type local_endpoint(const implementation_type& impl,
      boost::system::error_code& ec) const
  {
    return service_impl_.local_endpoint(impl, ec);
  }

  template <typename Protocol1, typename SocketService>
  boost::system::error_code accept(implementation_type& impl,
      basic_socket<Protocol1, SocketService>& peer,
      endpoint_type* peer_endpoint, boost::system::error_code& ec,
      typename enable_if<is_convertible<Protocol, Protocol1>::value>::type* = 0)
  {
    return service_impl_.accept(impl, peer, peer_endpoint, ec);
  }

  explicit signal_set_service(boost::asio::io_service& io_service)
    : boost::asio::detail::service_base<signal_set_service>(io_service),
      service_impl_(io_service)
  {
  }

  void construct(implementation_type& impl)
  {
    service_impl_.construct(impl);
  }

  void destroy(implementation_type& impl)
  {
    service_impl_.destroy(impl);
  }

  boost::system::error_code add(implementation_type& impl,
      int signal_number, boost::system::error_code& ec)
  {
    return service_impl_.add(impl, signal_number, ec);
  }

  boost::system::error_code remove(implementation_type& impl,
      int signal_number, boost::system::error_code& ec)
  {
    return service_impl_.remove(impl, signal_number, ec);
  }

  boost::system::error_code clear(implementation_type& impl,
      boost::system::error_code& ec)
  {
    return service_impl_.clear(impl, ec);
  }

  boost::system::error_code cancel(implementation_type& impl,
      boost::system::error_code& ec)
  {
    return service_impl_.cancel(impl, ec);
  }

  static typename Clock::duration to_wait_duration(
      const typename Clock::duration& d)
  {
    return d;
  }


inline const boost::system::error_category& get_system_category()
{
  return boost::system::system_category();
}


inline boost::system::error_code make_error_code(basic_errors e)
{
  return boost::system::error_code(
      static_cast<int>(e), get_system_category());
}

  mutable_buffer()
    : data_(0),
      size_(0)
  {
  }


inline void* buffer_cast_helper(const mutable_buffer& b)
{
#if defined(BOOST_ASIO_ENABLE_BUFFER_DEBUGGING)
  if (b.size_ && b.debug_check_)
    b.debug_check_();
#endif // BOOST_ASIO_ENABLE_BUFFER_DEBUGGING
  return b.data_;
}

  mutable_buffers_1(void* data, std::size_t size)
    : mutable_buffer(data, size)
  {
  }

  explicit mutable_buffers_1(const mutable_buffer& b)
    : mutable_buffer(b)
  {
  }

  const_iterator begin() const
  {
    return this;
  }

  const_iterator end() const
  {
    return begin() + 1;
  }

  const_buffer()
    : data_(0),
      size_(0)
  {
  }

  const_buffer(const mutable_buffer& b)
    : data_(boost::asio::detail::buffer_cast_helper(b)),
      size_(boost::asio::detail::buffer_size_helper(b))
#if defined(BOOST_ASIO_ENABLE_BUFFER_DEBUGGING)
      , debug_check_(b.get_debug_check())
#endif // BOOST_ASIO_ENABLE_BUFFER_DEBUGGING
  {
  }


inline const void* buffer_cast_helper(const const_buffer& b)
{
#if defined(BOOST_ASIO_ENABLE_BUFFER_DEBUGGING)
  if (b.size_ && b.debug_check_)
    b.debug_check_();
#endif // BOOST_ASIO_ENABLE_BUFFER_DEBUGGING
  return b.data_;
}

  const_buffers_1(const void* data, std::size_t size)
    : const_buffer(data, size)
  {
  }

  explicit const_buffers_1(const const_buffer& b)
    : const_buffer(b)
  {
  }

  const_iterator begin() const
  {
    return this;
  }

  const_iterator end() const
  {
    return begin() + 1;
  }

  const_iterator begin() const
  {
    return &buf_;
  }

  const_iterator end() const
  {
    return &buf_;
  }

inline std::size_t buffer_size(const mutable_buffer& b)
{
  return detail::buffer_size_helper(b);
}

template <typename PointerToPodType>
inline PointerToPodType buffer_cast(const mutable_buffer& b)
{
  return static_cast<PointerToPodType>(detail::buffer_cast_helper(b));
}

template <typename PointerToPodType>
inline PointerToPodType buffer_cast(const const_buffer& b)
{
  return static_cast<PointerToPodType>(detail::buffer_cast_helper(b));
}

inline mutable_buffer operator+(const mutable_buffer& b, std::size_t start)
{
  if (start > buffer_size(b))
    return mutable_buffer();
  char* new_data = buffer_cast<char*>(b) + start;
  std::size_t new_size = buffer_size(b) - start;
  return mutable_buffer(new_data, new_size
#if defined(BOOST_ASIO_ENABLE_BUFFER_DEBUGGING)
      , b.get_debug_check()
#endif // BOOST_ASIO_ENABLE_BUFFER_DEBUGGING
      );
}

inline mutable_buffers_1 buffer(const mutable_buffer& b)
{
  return mutable_buffers_1(b);
}

inline const_buffers_1 buffer(const const_buffer& b)
{
  return const_buffers_1(b);
}

template <typename PodType, std::size_t N>
inline mutable_buffers_1 buffer(PodType (&data)[N])
{
  return mutable_buffers_1(mutable_buffer(data, N * sizeof(PodType)));
}

template <typename PodType, std::size_t N>
inline const_buffers_1 buffer(const PodType (&data)[N])
{
  return const_buffers_1(const_buffer(data, N * sizeof(PodType)));
}

inline std::size_t buffer_copy(const mutable_buffer& target,
    const const_buffer& source)
{
  using namespace std; // For memcpy.
  std::size_t target_size = buffer_size(target);
  std::size_t source_size = buffer_size(source);
  std::size_t n = target_size < source_size ? target_size : source_size;
  memcpy(buffer_cast<void*>(target), buffer_cast<const void*>(source), n);
  return n;
}

  boost::asio::io_service& get_io_service()
  {
    return service.get_io_service();
  }

  explicit basic_io_object(boost::asio::io_service& io_service)
    : service(boost::asio::use_service<IoObjectService>(io_service))
  {
    service.construct(implementation);
  }

  ~basic_io_object()
  {
    service.destroy(implementation);
  }

  service_type& get_service()
  {
    return service;
  }

  const service_type& get_service() const
  {
    return service;
  }

  implementation_type& get_implementation()
  {
    return implementation;
  }

  const implementation_type& get_implementation() const
  {
    return implementation;
  }

  id() {}

    key() : type_info_(0), id_(0) {}

    key() : type_info_(0), id_(0) {}

  service_base(boost::asio::io_service& io_service)
    : boost::asio::io_service::service(io_service)
  {
  }

  explicit basic_signal_set(boost::asio::io_service& io_service)
    : basic_io_object<SignalSetService>(io_service)
  {
  }

  void add(int signal_number)
  {
    boost::system::error_code ec;
    this->service.add(this->implementation, signal_number, ec);
    boost::asio::detail::throw_error(ec, "add");
  }

  void remove(int signal_number)
  {
    boost::system::error_code ec;
    this->service.remove(this->implementation, signal_number, ec);
    boost::asio::detail::throw_error(ec, "remove");
  }

  void clear()
  {
    boost::system::error_code ec;
    this->service.clear(this->implementation, ec);
    boost::asio::detail::throw_error(ec, "clear");
  }

  void cancel()
  {
    boost::system::error_code ec;
    this->service.cancel(this->implementation, ec);
    boost::asio::detail::throw_error(ec, "cancel");
  }

  template <typename Arg>
  explicit buffered_read_stream(Arg& a)
    : next_layer_(a),
      storage_(default_buffer_size)
  {
  }

  next_layer_type& next_layer()
  {
    return next_layer_;
  }

  lowest_layer_type& lowest_layer()
  {
    return next_layer_.lowest_layer();
  }

  const lowest_layer_type& lowest_layer() const
  {
    return next_layer_.lowest_layer();
  }

  boost::asio::io_service& get_io_service()
  {
    return next_layer_.get_io_service();
  }

  void close()
  {
    next_layer_.close();
  }

  template <typename ConstBufferSequence>
  std::size_t write_some(const ConstBufferSequence& buffers)
  {
    return next_layer_.write_some(buffers);
  }

  template <typename ConstBufferSequence, typename WriteHandler>
  void async_write_some(const ConstBufferSequence& buffers,
      WriteHandler handler)
  {
    next_layer_.async_write_some(buffers, handler);
  }

  std::size_t fill()
  {
    detail::buffer_resize_guard<detail::buffered_stream_storage>
      resize_guard(storage_);
    std::size_t previous_size = storage_.size();
    storage_.resize(storage_.capacity());
    storage_.resize(previous_size + next_layer_.read_some(buffer(
            storage_.data() + previous_size,
            storage_.size() - previous_size)));
    resize_guard.commit();
    return storage_.size() - previous_size;
  }

    fill_handler(boost::asio::io_service& io_service,
        detail::buffered_stream_storage& storage,
        std::size_t previous_size, ReadHandler handler)
      : io_service_(io_service),
        storage_(storage),
        previous_size_(previous_size),
        handler_(handler)
    {
    }


    void operator()(const boost::system::error_code& ec,
        std::size_t bytes_transferred)
    {
      storage_.resize(previous_size_ + bytes_transferred);
      io_service_.dispatch(detail::bind_handler(
            handler_, ec, bytes_transferred));
    }

  template <typename ReadHandler>
  void async_fill(ReadHandler handler)
  {
    std::size_t previous_size = storage_.size();
    storage_.resize(storage_.capacity());
    next_layer_.async_read_some(
        buffer(
          storage_.data() + previous_size,
          storage_.size() - previous_size),
        fill_handler<ReadHandler>(get_io_service(),
          storage_, previous_size, handler));
  }

  template <typename MutableBufferSequence>
  std::size_t read_some(const MutableBufferSequence& buffers)
  {
    if (boost::asio::buffer_size(buffers) == 0)
      return 0;

    if (storage_.empty())
      fill();

    return copy(buffers);
  }

    read_some_handler(boost::asio::io_service& io_service,
        detail::buffered_stream_storage& storage,
        const MutableBufferSequence& buffers, ReadHandler handler)
      : io_service_(io_service),
        storage_(storage),
        buffers_(buffers),
        handler_(handler)
    {
    }


    void operator()(const boost::system::error_code& ec, std::size_t)
    {
      if (ec || storage_.empty())
      {
        std::size_t length = 0;
        io_service_.dispatch(detail::bind_handler(handler_, ec, length));
      }
      else
      {
        std::size_t bytes_copied = boost::asio::buffer_copy(
            buffers_, storage_.data(), storage_.size());
        storage_.consume(bytes_copied);
        io_service_.dispatch(detail::bind_handler(handler_, ec, bytes_copied));
      }
    }

  template <typename MutableBufferSequence, typename ReadHandler>
  void async_read_some(const MutableBufferSequence& buffers,
      ReadHandler handler)
  {
    if (boost::asio::buffer_size(buffers) == 0)
    {
      get_io_service().post(detail::bind_handler(
            handler, boost::system::error_code(), 0));
    }
    else if (storage_.empty())
    {
      async_fill(read_some_handler<MutableBufferSequence, ReadHandler>(
            get_io_service(), storage_, buffers, handler));
    }
    else
    {
      std::size_t length = copy(buffers);
      get_io_service().post(detail::bind_handler(
            handler, boost::system::error_code(), length));
    }
  }

  template <typename MutableBufferSequence>
  std::size_t peek(const MutableBufferSequence& buffers)
  {
    if (storage_.empty())
      fill();
    return peek_copy(buffers);
  }

  std::size_t in_avail()
  {
    return storage_.size();
  }

  template <typename MutableBufferSequence>
  std::size_t copy(const MutableBufferSequence& buffers)
  {
    std::size_t bytes_copied = boost::asio::buffer_copy(
        buffers, storage_.data(), storage_.size());
    storage_.consume(bytes_copied);
    return bytes_copied;
  }

  template <typename MutableBufferSequence>
  std::size_t peek_copy(const MutableBufferSequence& buffers)
  {
    return boost::asio::buffer_copy(buffers, storage_.data(), storage_.size());
  }

  explicit raw_socket_service(boost::asio::io_service& io_service)
    : boost::asio::detail::service_base<
        raw_socket_service<Protocol> >(io_service),
      service_impl_(io_service)
  {
  }

  void construct(implementation_type& impl)
  {
    service_impl_.construct(impl);
  }

  void destroy(implementation_type& impl)
  {
    service_impl_.destroy(impl);
  }

  boost::system::error_code open(implementation_type& impl,
      const protocol_type& protocol, boost::system::error_code& ec)
  {
    if (protocol.type() == SOCK_RAW)
      service_impl_.open(impl, protocol, ec);
    else
      ec = boost::asio::error::invalid_argument;
    return ec;
  }

  boost::system::error_code assign(implementation_type& impl,
      const protocol_type& protocol, const native_handle_type& native_socket,
      boost::system::error_code& ec)
  {
    return service_impl_.assign(impl, protocol, native_socket, ec);
  }

  bool is_open(const implementation_type& impl) const
  {
    return service_impl_.is_open(impl);
  }

  boost::system::error_code close(implementation_type& impl,
      boost::system::error_code& ec)
  {
    return service_impl_.close(impl, ec);
  }

  native_type native(implementation_type& impl)
  {
    return service_impl_.native_handle(impl);
  }

  native_handle_type native_handle(implementation_type& impl)
  {
    return service_impl_.native_handle(impl);
  }

  boost::system::error_code cancel(implementation_type& impl,
      boost::system::error_code& ec)
  {
    return service_impl_.cancel(impl, ec);
  }

  bool at_mark(const implementation_type& impl,
      boost::system::error_code& ec) const
  {
    return service_impl_.at_mark(impl, ec);
  }

  std::size_t available(const implementation_type& impl,
      boost::system::error_code& ec) const
  {
    return service_impl_.available(impl, ec);
  }

  boost::system::error_code bind(implementation_type& impl,
      const endpoint_type& endpoint, boost::system::error_code& ec)
  {
    return service_impl_.bind(impl, endpoint, ec);
  }

  boost::system::error_code connect(implementation_type& impl,
      const endpoint_type& peer_endpoint, boost::system::error_code& ec)
  {
    return service_impl_.connect(impl, peer_endpoint, ec);
  }

  coroutine() : value_(0) {}

  bool is_child() const { return value_ < 0; }

  bool is_parent() const { return !is_child(); }

  bool is_complete() const { return value_ == -1; }

  coroutine_ref(coroutine& c) : value_(c.value_), modified_(false) {}

  coroutine_ref(coroutine* c) : value_(c->value_), modified_(false) {}

  ~coroutine_ref() { if (!modified_) value_ = -1; }

  operator int() const { return value_; }

  int& operator=(int v) { modified_ = true; return value_ = v; }
coroutine():value_(0){}
boolis_child()const{returnvalue_<0;}
boolis_parent()const{return!is_child();}
boolis_complete()const{returnvalue_==-1;}
coroutine_ref(coroutine&c):value_(c.value_),modified_(false){}
coroutine_ref(coroutine*c):value_(c->value_),modified_(false){}
~coroutine_ref(){if(!modified_)value_=-1;}
operatorint()const{returnvalue_;}
int&operator=(intv){modified_=true;returnvalue_=v;}

  explicit basic_streambuf(
      std::size_t maximum_size = (std::numeric_limits<std::size_t>::max)(),
      const Allocator& allocator = Allocator())
    : max_size_(maximum_size),
      buffer_(allocator)
  {
    std::size_t pend = (std::min<std::size_t>)(max_size_, buffer_delta);
    buffer_.resize((std::max<std::size_t>)(pend, 1));
    setg(&buffer_[0], &buffer_[0], &buffer_[0]);
    setp(&buffer_[0], &buffer_[0] + pend);
  }

  std::size_t size() const
  {
    return pptr() - gptr();
  }

  std::size_t max_size() const
  {
    return max_size_;
  }

  const_buffers_type data() const
  {
    return boost::asio::buffer(boost::asio::const_buffer(gptr(),
          (pptr() - gptr()) * sizeof(char_type)));
  }

  mutable_buffers_type prepare(std::size_t n)
  {
    reserve(n);
    return boost::asio::buffer(boost::asio::mutable_buffer(
          pptr(), n * sizeof(char_type)));
  }

  void commit(std::size_t n)
  {
    if (pptr() + n > epptr())
      n = epptr() - pptr();
    pbump(static_cast<int>(n));
    setg(eback(), gptr(), pptr());
  }

  void consume(std::size_t n)
  {
    if (egptr() < pptr())
      setg(&buffer_[0], gptr(), pptr());
    if (gptr() + n > pptr())
      n = pptr() - gptr();
    gbump(static_cast<int>(n));
  }

  int_type underflow()
  {
    if (gptr() < pptr())
    {
      setg(&buffer_[0], gptr(), pptr());
      return traits_type::to_int_type(*gptr());
    }
    else
    {
      return traits_type::eof();
    }
  }

  int_type overflow(int_type c)
  {
    if (!traits_type::eq_int_type(c, traits_type::eof()))
    {
      if (pptr() == epptr())
      {
        std::size_t buffer_size = pptr() - gptr();
        if (buffer_size < max_size_ && max_size_ - buffer_size < buffer_delta)
        {
          reserve(max_size_ - buffer_size);
        }
        else
        {
          reserve(buffer_delta);
        }
      }

      *pptr() = traits_type::to_char_type(c);
      pbump(1);
      return c;
    }

    return traits_type::not_eof(c);
  }


  void reserve(std::size_t n)
  {
    // Get current stream positions as offsets.
    std::size_t gnext = gptr() - &buffer_[0];
    std::size_t pnext = pptr() - &buffer_[0];
    std::size_t pend = epptr() - &buffer_[0];

    // Check if there is already enough space in the put area.
    if (n <= pend - pnext)
    {
      return;
    }

    // Shift existing contents of get area to start of buffer.
    if (gnext > 0)
    {
      pnext -= gnext;
      std::memmove(&buffer_[0], &buffer_[0] + gnext, pnext);
    }

    // Ensure buffer is large enough to hold at least the specified size.
    if (n > pend - pnext)
    {
      if (n <= max_size_ && pnext <= max_size_ - n)
      {
        pend = pnext + n;
        buffer_.resize((std::max<std::size_t>)(pend, 1));
      }
      else
      {
        std::length_error ex("boost::asio::streambuf too long");
        boost::asio::detail::throw_exception(ex);
      }
    }

    // Update stream positions.
    setg(&buffer_[0], &buffer_[0], &buffer_[0] + pnext);
    setp(&buffer_[0] + pnext, &buffer_[0] + pend);
  }

template <typename Allocator>
inline std::size_t read_size_helper(
    basic_streambuf<Allocator>& sb, std::size_t max_size)
{
  return std::min<std::size_t>(512,
      std::min<std::size_t>(max_size, sb.max_size() - sb.size()));
}

  explicit datagram_socket_service(boost::asio::io_service& io_service)
    : boost::asio::detail::service_base<
        datagram_socket_service<Protocol> >(io_service),
      service_impl_(io_service)
  {
  }

  void construct(implementation_type& impl)
  {
    service_impl_.construct(impl);
  }

  void destroy(implementation_type& impl)
  {
    service_impl_.destroy(impl);
  }

  boost::system::error_code open(implementation_type& impl,
      const protocol_type& protocol, boost::system::error_code& ec)
  {
    if (protocol.type() == SOCK_DGRAM)
      service_impl_.open(impl, protocol, ec);
    else
      ec = boost::asio::error::invalid_argument;
    return ec;
  }

  boost::system::error_code assign(implementation_type& impl,
      const protocol_type& protocol, const native_handle_type& native_socket,
      boost::system::error_code& ec)
  {
    return service_impl_.assign(impl, protocol, native_socket, ec);
  }

  bool is_open(const implementation_type& impl) const
  {
    return service_impl_.is_open(impl);
  }

  boost::system::error_code close(implementation_type& impl,
      boost::system::error_code& ec)
  {
    return service_impl_.close(impl, ec);
  }

  native_type native(implementation_type& impl)
  {
    return service_impl_.native_handle(impl);
  }

  native_handle_type native_handle(implementation_type& impl)
  {
    return service_impl_.native_handle(impl);
  }

  boost::system::error_code cancel(implementation_type& impl,
      boost::system::error_code& ec)
  {
    return service_impl_.cancel(impl, ec);
  }

  bool at_mark(const implementation_type& impl,
      boost::system::error_code& ec) const
  {
    return service_impl_.at_mark(impl, ec);
  }

  std::size_t available(const implementation_type& impl,
      boost::system::error_code& ec) const
  {
    return service_impl_.available(impl, ec);
  }

  boost::system::error_code bind(implementation_type& impl,
      const endpoint_type& endpoint, boost::system::error_code& ec)
  {
    return service_impl_.bind(impl, endpoint, ec);
  }

  boost::system::error_code connect(implementation_type& impl,
      const endpoint_type& peer_endpoint, boost::system::error_code& ec)
  {
    return service_impl_.connect(impl, peer_endpoint, ec);
  }

inline bool asio_handler_is_continuation(...)
{
  return false;
}

  template <typename Arg>
  explicit buffered_stream(Arg& a)
    : inner_stream_impl_(a),
      stream_impl_(inner_stream_impl_)
  {
  }

  next_layer_type& next_layer()
  {
    return stream_impl_.next_layer().next_layer();
  }

  lowest_layer_type& lowest_layer()
  {
    return stream_impl_.lowest_layer();
  }

  const lowest_layer_type& lowest_layer() const
  {
    return stream_impl_.lowest_layer();
  }

  boost::asio::io_service& get_io_service()
  {
    return stream_impl_.get_io_service();
  }

  void close()
  {
    stream_impl_.close();
  }

  std::size_t flush()
  {
    return stream_impl_.next_layer().flush();
  }

  template <typename WriteHandler>
  void async_flush(WriteHandler handler)
  {
    return stream_impl_.next_layer().async_flush(handler);
  }

  template <typename ConstBufferSequence>
  std::size_t write_some(const ConstBufferSequence& buffers)
  {
    return stream_impl_.write_some(buffers);
  }

  template <typename ConstBufferSequence, typename WriteHandler>
  void async_write_some(const ConstBufferSequence& buffers,
      WriteHandler handler)
  {
    stream_impl_.async_write_some(buffers, handler);
  }

  std::size_t fill()
  {
    return stream_impl_.fill();
  }

  template <typename ReadHandler>
  void async_fill(ReadHandler handler)
  {
    stream_impl_.async_fill(handler);
  }

  template <typename MutableBufferSequence>
  std::size_t read_some(const MutableBufferSequence& buffers)
  {
    return stream_impl_.read_some(buffers);
  }

  template <typename MutableBufferSequence, typename ReadHandler>
  void async_read_some(const MutableBufferSequence& buffers,
      ReadHandler handler)
  {
    stream_impl_.async_read_some(buffers, handler);
  }

  template <typename MutableBufferSequence>
  std::size_t peek(const MutableBufferSequence& buffers)
  {
    return stream_impl_.peek(buffers);
  }

  std::size_t in_avail()
  {
    return stream_impl_.in_avail();
  }

template <typename Function>
inline void asio_handler_invoke(Function function, ...)
{
  function();
}

  template <typename Arg>
  explicit buffered_write_stream(Arg& a)
    : next_layer_(a),
      storage_(default_buffer_size)
  {
  }

  next_layer_type& next_layer()
  {
    return next_layer_;
  }

  lowest_layer_type& lowest_layer()
  {
    return next_layer_.lowest_layer();
  }

  const lowest_layer_type& lowest_layer() const
  {
    return next_layer_.lowest_layer();
  }

  boost::asio::io_service& get_io_service()
  {
    return next_layer_.get_io_service();
  }

  void close()
  {
    next_layer_.close();
  }

  std::size_t flush()
  {
    std::size_t bytes_written = write(next_layer_,
        buffer(storage_.data(), storage_.size()));
    storage_.consume(bytes_written);
    return bytes_written;
  }

    flush_handler(boost::asio::io_service& io_service,
        detail::buffered_stream_storage& storage, WriteHandler handler)
      : io_service_(io_service),
        storage_(storage),
        handler_(handler)
    {
    }


    void operator()(const boost::system::error_code& ec,
        std::size_t bytes_written)
    {
      storage_.consume(bytes_written);
      io_service_.dispatch(detail::bind_handler(handler_, ec, bytes_written));
    }

  template <typename WriteHandler>
  void async_flush(WriteHandler handler)
  {
    async_write(next_layer_, buffer(storage_.data(), storage_.size()),
        flush_handler<WriteHandler>(get_io_service(), storage_, handler));
  }

  template <typename ConstBufferSequence>
  std::size_t write_some(const ConstBufferSequence& buffers)
  {
    if (boost::asio::buffer_size(buffers) == 0)
      return 0;

    if (storage_.size() == storage_.capacity())
      flush();

    return copy(buffers);
  }

    write_some_handler(boost::asio::io_service& io_service,
        detail::buffered_stream_storage& storage,
        const ConstBufferSequence& buffers, WriteHandler handler)
      : io_service_(io_service),
        storage_(storage),
        buffers_(buffers),
        handler_(handler)
    {
    }


    void operator()(const boost::system::error_code& ec, std::size_t)
    {
      if (ec)
      {
        std::size_t length = 0;
        io_service_.dispatch(detail::bind_handler(handler_, ec, length));
      }
      else
      {
        std::size_t orig_size = storage_.size();
        std::size_t space_avail = storage_.capacity() - orig_size;
        std::size_t bytes_avail = boost::asio::buffer_size(buffers_);
        std::size_t length = bytes_avail < space_avail
          ? bytes_avail : space_avail;
        storage_.resize(orig_size + length);
        std::size_t bytes_copied = boost::asio::buffer_copy(
            storage_.data() + orig_size, buffers_, length);

        io_service_.dispatch(detail::bind_handler(handler_, ec, bytes_copied));
      }
    }

  template <typename ConstBufferSequence, typename WriteHandler>
  void async_write_some(const ConstBufferSequence& buffers,
      WriteHandler handler)
  {
    if (boost::asio::buffer_size(buffers) == 0)
    {
      get_io_service().post(detail::bind_handler(
            handler, boost::system::error_code(), 0));
    }
    else if (storage_.size() == storage_.capacity())
    {
      async_flush(write_some_handler<ConstBufferSequence, WriteHandler>(
            get_io_service(), storage_, buffers, handler));
    }
    else
    {
      std::size_t bytes_copied = copy(buffers);
      get_io_service().post(detail::bind_handler(
            handler, boost::system::error_code(), bytes_copied));
    }
  }

  template <typename MutableBufferSequence>
  std::size_t read_some(const MutableBufferSequence& buffers)
  {
    return next_layer_.read_some(buffers);
  }

  template <typename MutableBufferSequence, typename ReadHandler>
  void async_read_some(const MutableBufferSequence& buffers,
      ReadHandler handler)
  {
    next_layer_.async_read_some(buffers, handler);
  }

  template <typename MutableBufferSequence>
  std::size_t peek(const MutableBufferSequence& buffers)
  {
    return next_layer_.peek(buffers);
  }

  std::size_t in_avail()
  {
    return next_layer_.in_avail();
  }

  template <typename ConstBufferSequence>
  std::size_t copy(const ConstBufferSequence& buffers)
  {
    std::size_t orig_size = storage_.size();
    std::size_t space_avail = storage_.capacity() - orig_size;
    std::size_t bytes_avail = boost::asio::buffer_size(buffers);
    std::size_t length = bytes_avail < space_avail ? bytes_avail : space_avail;
    storage_.resize(orig_size + length);
    return boost::asio::buffer_copy(
        storage_.data() + orig_size, buffers, length);
  }

  buffers_iterator()
    : current_buffer_(),
      current_buffer_position_(0),
      begin_(),
      current_(),
      end_(),
      position_(0)
  {
  }

  static buffers_iterator begin(const BufferSequence& buffers)
#if defined(__GNUC__) && (__GNUC__ == 4) && (__GNUC_MINOR__ == 3)
    __attribute__ ((__noinline__))
#endif // defined(__GNUC__) && (__GNUC__ == 4) && (__GNUC_MINOR__ == 3)
  {
    buffers_iterator new_iter;
    new_iter.begin_ = buffers.begin();
    new_iter.current_ = buffers.begin();
    new_iter.end_ = buffers.end();
    while (new_iter.current_ != new_iter.end_)
    {
      new_iter.current_buffer_ = *new_iter.current_;
      if (boost::asio::buffer_size(new_iter.current_buffer_) > 0)
        break;
      ++new_iter.current_;
    }
    return new_iter;
  }

  static buffers_iterator end(const BufferSequence& buffers)
#if defined(__GNUC__) && (__GNUC__ == 4) && (__GNUC_MINOR__ == 3)
    __attribute__ ((__noinline__))
#endif // defined(__GNUC__) && (__GNUC__ == 4) && (__GNUC_MINOR__ == 3)
  {
    buffers_iterator new_iter;
    new_iter.begin_ = buffers.begin();
    new_iter.current_ = buffers.begin();
    new_iter.end_ = buffers.end();
    while (new_iter.current_ != new_iter.end_)
    {
      buffer_type buffer = *new_iter.current_;
      new_iter.position_ += boost::asio::buffer_size(buffer);
      ++new_iter.current_;
    }
    return new_iter;
  }

  reference operator*() const
  {
    return dereference();
  }

  pointer operator->() const
  {
    return &dereference();
  }

  reference operator[](std::ptrdiff_t difference) const
  {
    buffers_iterator tmp(*this);
    tmp.advance(difference);
    return *tmp;
  }

  buffers_iterator& operator++()
  {
    increment();
    return *this;
  }

  buffers_iterator operator++(int)
  {
    buffers_iterator tmp(*this);
    ++*this;
    return tmp;
  }

  buffers_iterator& operator--()
  {
    decrement();
    return *this;
  }

  buffers_iterator operator--(int)
  {
    buffers_iterator tmp(*this);
    --*this;
    return tmp;
  }

  buffers_iterator& operator+=(std::ptrdiff_t difference)
  {
    advance(difference);
    return *this;
  }

  buffers_iterator& operator-=(std::ptrdiff_t difference)
  {
    advance(-difference);
    return *this;
  }

  reference dereference() const
  {
    return buffer_cast<pointer>(current_buffer_)[current_buffer_position_];
  }

  bool equal(const buffers_iterator& other) const
  {
    return position_ == other.position_;
  }

  void increment()
  {
    BOOST_ASIO_ASSERT(current_ != end_ && "iterator out of bounds");
    ++position_;

    // Check if the increment can be satisfied by the current buffer.
    ++current_buffer_position_;
    if (current_buffer_position_ != boost::asio::buffer_size(current_buffer_))
      return;

    // Find the next non-empty buffer.
    ++current_;
    current_buffer_position_ = 0;
    while (current_ != end_)
    {
      current_buffer_ = *current_;
      if (boost::asio::buffer_size(current_buffer_) > 0)
        return;
      ++current_;
    }
  }

  void decrement()
  {
    BOOST_ASIO_ASSERT(position_ > 0 && "iterator out of bounds");
    --position_;

    // Check if the decrement can be satisfied by the current buffer.
    if (current_buffer_position_ != 0)
    {
      --current_buffer_position_;
      return;
    }

    // Find the previous non-empty buffer.
    typename BufferSequence::const_iterator iter = current_;
    while (iter != begin_)
    {
      --iter;
      buffer_type buffer = *iter;
      std::size_t buffer_size = boost::asio::buffer_size(buffer);
      if (buffer_size > 0)
      {
        current_ = iter;
        current_buffer_ = buffer;
        current_buffer_position_ = buffer_size - 1;
        return;
      }
    }
  }

  void advance(std::ptrdiff_t n)
  {
    if (n > 0)
    {
      BOOST_ASIO_ASSERT(current_ != end_ && "iterator out of bounds");
      for (;;)
      {
        std::ptrdiff_t current_buffer_balance
          = boost::asio::buffer_size(current_buffer_)
          - current_buffer_position_;

        // Check if the advance can be satisfied by the current buffer.
        if (current_buffer_balance > n)
        {
          position_ += n;
          current_buffer_position_ += n;
          return;
        }

        // Update position.
        n -= current_buffer_balance;
        position_ += current_buffer_balance;

        // Move to next buffer. If it is empty then it will be skipped on the
        // next iteration of this loop.
        if (++current_ == end_)
        {
          BOOST_ASIO_ASSERT(n == 0 && "iterator out of bounds");
          current_buffer_ = buffer_type();
          current_buffer_position_ = 0;
          return;
        }
        current_buffer_ = *current_;
        current_buffer_position_ = 0;
      }
    }
    else if (n < 0)
    {
      std::size_t abs_n = -n;
      BOOST_ASIO_ASSERT(position_ >= abs_n && "iterator out of bounds");
      for (;;)
      {
        // Check if the advance can be satisfied by the current buffer.
        if (current_buffer_position_ >= abs_n)
        {
          position_ -= abs_n;
          current_buffer_position_ -= abs_n;
          return;
        }

        // Update position.
        abs_n -= current_buffer_position_;
        position_ -= current_buffer_position_;

        // Check if we've reached the beginning of the buffers.
        if (current_ == begin_)
        {
          BOOST_ASIO_ASSERT(abs_n == 0 && "iterator out of bounds");
          current_buffer_position_ = 0;
          return;
        }

        // Find the previous non-empty buffer.
        typename BufferSequence::const_iterator iter = current_;
        while (iter != begin_)
        {
          --iter;
          buffer_type buffer = *iter;
          std::size_t buffer_size = boost::asio::buffer_size(buffer);
          if (buffer_size > 0)
          {
            current_ = iter;
            current_buffer_ = buffer;
            current_buffer_position_ = buffer_size;
            break;
          }
        }
      }
    }
  }

  std::ptrdiff_t distance_to(const buffers_iterator& other) const
  {
    return other.position_ - position_;
  }

template <typename BufferSequence>
inline buffers_iterator<BufferSequence> buffers_begin(
    const BufferSequence& buffers)
{
  return buffers_iterator<BufferSequence>::begin(buffers);
}

template <typename BufferSequence>
inline buffers_iterator<BufferSequence> buffers_end(
    const BufferSequence& buffers)
{
  return buffers_iterator<BufferSequence>::end(buffers);
}

  explicit basic_socket(boost::asio::io_service& io_service)
    : basic_io_object<SocketService>(io_service)
  {
  }

  lowest_layer_type& lowest_layer()
  {
    return *this;
  }

  const lowest_layer_type& lowest_layer() const
  {
    return *this;
  }

  void open(const protocol_type& protocol = protocol_type())
  {
    boost::system::error_code ec;
    this->get_service().open(this->get_implementation(), protocol, ec);
    boost::asio::detail::throw_error(ec, "open");
  }

  void assign(const protocol_type& protocol,
      const native_handle_type& native_socket)
  {
    boost::system::error_code ec;
    this->get_service().assign(this->get_implementation(),
        protocol, native_socket, ec);
    boost::asio::detail::throw_error(ec, "assign");
  }

  bool is_open() const
  {
    return this->get_service().is_open(this->get_implementation());
  }

  void close()
  {
    boost::system::error_code ec;
    this->get_service().close(this->get_implementation(), ec);
    boost::asio::detail::throw_error(ec, "close");
  }

  native_type native()
  {
    return this->get_service().native_handle(this->get_implementation());
  }

  native_handle_type native_handle()
  {
    return this->get_service().native_handle(this->get_implementation());
  }

  void cancel()
  {
    boost::system::error_code ec;
    this->get_service().cancel(this->get_implementation(), ec);
    boost::asio::detail::throw_error(ec, "cancel");
  }

  bool at_mark() const
  {
    boost::system::error_code ec;
    bool b = this->get_service().at_mark(this->get_implementation(), ec);
    boost::asio::detail::throw_error(ec, "at_mark");
    return b;
  }

  std::size_t available() const
  {
    boost::system::error_code ec;
    std::size_t s = this->get_service().available(
        this->get_implementation(), ec);
    boost::asio::detail::throw_error(ec, "available");
    return s;
  }

  void bind(const endpoint_type& endpoint)
  {
    boost::system::error_code ec;
    this->get_service().bind(this->get_implementation(), endpoint, ec);
    boost::asio::detail::throw_error(ec, "bind");
  }

  void connect(const endpoint_type& peer_endpoint)
  {
    boost::system::error_code ec;
    if (!is_open())
    {
      this->get_service().open(this->get_implementation(),
          peer_endpoint.protocol(), ec);
      boost::asio::detail::throw_error(ec, "connect");
    }
    this->get_service().connect(this->get_implementation(), peer_endpoint, ec);
    boost::asio::detail::throw_error(ec, "connect");
  }

  explicit stream_socket_service(boost::asio::io_service& io_service)
    : boost::asio::detail::service_base<
        stream_socket_service<Protocol> >(io_service),
      service_impl_(io_service)
  {
  }

  void construct(implementation_type& impl)
  {
    service_impl_.construct(impl);
  }

  void destroy(implementation_type& impl)
  {
    service_impl_.destroy(impl);
  }

  boost::system::error_code open(implementation_type& impl,
      const protocol_type& protocol, boost::system::error_code& ec)
  {
    if (protocol.type() == SOCK_STREAM)
      service_impl_.open(impl, protocol, ec);
    else
      ec = boost::asio::error::invalid_argument;
    return ec;
  }

  boost::system::error_code assign(implementation_type& impl,
      const protocol_type& protocol, const native_handle_type& native_socket,
      boost::system::error_code& ec)
  {
    return service_impl_.assign(impl, protocol, native_socket, ec);
  }

  bool is_open(const implementation_type& impl) const
  {
    return service_impl_.is_open(impl);
  }

  boost::system::error_code close(implementation_type& impl,
      boost::system::error_code& ec)
  {
    return service_impl_.close(impl, ec);
  }

  native_type native(implementation_type& impl)
  {
    return service_impl_.native_handle(impl);
  }

  native_handle_type native_handle(implementation_type& impl)
  {
    return service_impl_.native_handle(impl);
  }

  boost::system::error_code cancel(implementation_type& impl,
      boost::system::error_code& ec)
  {
    return service_impl_.cancel(impl, ec);
  }

  bool at_mark(const implementation_type& impl,
      boost::system::error_code& ec) const
  {
    return service_impl_.at_mark(impl, ec);
  }

  std::size_t available(const implementation_type& impl,
      boost::system::error_code& ec) const
  {
    return service_impl_.available(impl, ec);
  }

  boost::system::error_code bind(implementation_type& impl,
      const endpoint_type& endpoint, boost::system::error_code& ec)
  {
    return service_impl_.bind(impl, endpoint, ec);
  }

  boost::system::error_code connect(implementation_type& impl,
      const endpoint_type& peer_endpoint, boost::system::error_code& ec)
  {
    return service_impl_.connect(impl, peer_endpoint, ec);
  }

  basic_yield_context(
      const detail::weak_ptr<callee_type>& coro,
      caller_type& ca, Handler& handler)
    : coro_(coro),
      ca_(ca),
      handler_(handler),
      ec_(0)
  {
  }

  basic_yield_context operator[](boost::system::error_code& ec) const
  {
    basic_yield_context tmp(*this);
    tmp.ec_ = &ec;
    return tmp;
  }

  basic_endpoint()
    : impl_()
  {
  }

  basic_endpoint(const InternetProtocol& internet_protocol,
      unsigned short port_num)
    : impl_(internet_protocol.family(), port_num)
  {
  }

  basic_endpoint(const basic_endpoint& other)
    : impl_(other.impl_)
  {
  }

  basic_endpoint& operator=(const basic_endpoint& other)
  {
    impl_ = other.impl_;
    return *this;
  }

  protocol_type protocol() const
  {
    if (impl_.is_v4())
      return InternetProtocol::v4();
    return InternetProtocol::v6();
  }

  data_type* data()
  {
    return impl_.data();
  }

  const data_type* data() const
  {
    return impl_.data();
  }

  std::size_t size() const
  {
    return impl_.size();
  }

  void resize(std::size_t new_size)
  {
    impl_.resize(new_size);
  }

  std::size_t capacity() const
  {
    return impl_.capacity();
  }

  unsigned short port() const
  {
    return impl_.port();
  }

  void port(unsigned short port_num)
  {
    impl_.port(port_num);
  }

  boost::asio::ip::address address() const
  {
    return impl_.address();
  }

  bool is_v4() const
  {
    return type_ == ipv4;
  }

  bool is_v6() const
  {
    return type_ == ipv6;
  }

  basic_resolver_iterator()
    : index_(0)
  {
  }

  static basic_resolver_iterator create(
      boost::asio::detail::addrinfo_type* address_info,
      const std::string& host_name, const std::string& service_name)
  {
    basic_resolver_iterator iter;
    if (!address_info)
      return iter;

    std::string actual_host_name = host_name;
    if (address_info->ai_canonname)
      actual_host_name = address_info->ai_canonname;

    iter.values_.reset(new values_type);

    while (address_info)
    {
      if (address_info->ai_family == PF_INET
          || address_info->ai_family == PF_INET6)
      {
        using namespace std; // For memcpy.
        typename InternetProtocol::endpoint endpoint;
        endpoint.resize(static_cast<std::size_t>(address_info->ai_addrlen));
        memcpy(endpoint.data(), address_info->ai_addr,
            address_info->ai_addrlen);
        iter.values_->push_back(
            basic_resolver_entry<InternetProtocol>(endpoint,
              actual_host_name, service_name));
      }
      address_info = address_info->ai_next;
    }

    return iter;
  }

  unsigned long scope_id() const
  {
    return scope_id_;
  }

  void scope_id(unsigned long id)
  {
    scope_id_ = id;
  }

  static address_v6 any()
  {
    return address_v6();
  }

  static icmp v4()
  {
    return icmp(IPPROTO_ICMP, PF_INET);
  }

  static icmp v6()
  {
    return icmp(IPPROTO_ICMPV6, PF_INET6);
  }

  int type() const
  {
    return SOCK_RAW;
  }

  int protocol() const
  {
    return protocol_;
  }

  int family() const
  {
    return family_;
  }

  explicit icmp(int protocol_id, int protocol_family)
    : protocol_(protocol_id),
      family_(protocol_family)
  {
  }

  address_v4()
  {
    addr_.s_addr = 0;
  }

  address_v4(const address_v4& other)
    : addr_(other.addr_)
  {
  }

  address_v4& operator=(const address_v4& other)
  {
    addr_ = other.addr_;
    return *this;
  }

  static address_v4 any()
  {
    return address_v4();
  }

  static address_v4 loopback()
  {
    return address_v4(0x7F000001);
  }

  static address_v4 broadcast()
  {
    return address_v4(0xFFFFFFFF);
  }

  static udp v4()
  {
    return udp(PF_INET);
  }

  static udp v6()
  {
    return udp(PF_INET6);
  }

  int type() const
  {
    return SOCK_DGRAM;
  }

  int protocol() const
  {
    return IPPROTO_UDP;
  }

  int family() const
  {
    return family_;
  }

  explicit udp(int protocol_family)
    : family_(protocol_family)
  {
  }

  basic_resolver_entry()
  {
  }

  endpoint_type endpoint() const
  {
    return endpoint_;
  }

  operator endpoint_type() const
  {
    return endpoint_;
  }

  std::string host_name() const
  {
    return host_name_;
  }

  std::string service_name() const
  {
    return service_name_;
  }

  ~resolver_query_base()
  {
  }

  basic_resolver_query(const std::string& service,
      resolver_query_base::flags resolve_flags = passive | address_configured)
    : hints_(),
      host_name_(),
      service_name_(service)
  {
    typename InternetProtocol::endpoint endpoint;
    hints_.ai_flags = static_cast<int>(resolve_flags);
    hints_.ai_family = PF_UNSPEC;
    hints_.ai_socktype = endpoint.protocol().type();
    hints_.ai_protocol = endpoint.protocol().protocol();
    hints_.ai_addrlen = 0;
    hints_.ai_canonname = 0;
    hints_.ai_addr = 0;
    hints_.ai_next = 0;
  }

  const boost::asio::detail::addrinfo_type& hints() const
  {
    return hints_;
  }

  std::string host_name() const
  {
    return host_name_;
  }

  std::string service_name() const
  {
    return service_name_;
  }

  explicit resolver_service(boost::asio::io_service& io_service)
    : boost::asio::detail::service_base<
        resolver_service<InternetProtocol> >(io_service),
      service_impl_(io_service)
  {
  }

  void construct(implementation_type& impl)
  {
    service_impl_.construct(impl);
  }

  void destroy(implementation_type& impl)
  {
    service_impl_.destroy(impl);
  }

  void cancel(implementation_type& impl)
  {
    service_impl_.cancel(impl);
  }

  iterator_type resolve(implementation_type& impl, const query_type& query,
      boost::system::error_code& ec)
  {
    return service_impl_.resolve(impl, query, ec);
  }

  static tcp v4()
  {
    return tcp(PF_INET);
  }

  static tcp v6()
  {
    return tcp(PF_INET6);
  }

  int type() const
  {
    return SOCK_STREAM;
  }

  int protocol() const
  {
    return IPPROTO_TCP;
  }

  int family() const
  {
    return family_;
  }

  explicit tcp(int protocol_family)
    : family_(protocol_family)
  {
  }

  endpoint(const endpoint& other)
    : data_(other.data_)
  {
  }

  endpoint& operator=(const endpoint& other)
  {
    data_ = other.data_;
    return *this;
  }

  boost::asio::detail::socket_addr_type* data()
  {
    return &data_.base;
  }

  std::size_t size() const
  {
    if (is_v4())
      return sizeof(boost::asio::detail::sockaddr_in4_type);
    else
      return sizeof(boost::asio::detail::sockaddr_in6_type);
  }

  std::size_t capacity() const
  {
    return sizeof(data_);
  }

  bool is_v4() const
  {
    return data_.base.sa_family == AF_INET;
  }

  multicast_enable_loopback()
    : ipv4_value_(0),
      ipv6_value_(0)
  {
  }

  explicit multicast_enable_loopback(bool v)
    : ipv4_value_(v ? 1 : 0),
      ipv6_value_(v ? 1 : 0)
  {
  }

  multicast_enable_loopback& operator=(bool v)
  {
    ipv4_value_ = v ? 1 : 0;
    ipv6_value_ = v ? 1 : 0;
    return *this;
  }

  bool value() const
  {
    return !!ipv4_value_;
  }

  operator bool() const
  {
    return !!ipv4_value_;
  }

  bool operator!() const
  {
    return !ipv4_value_;
  }

  template <typename Protocol>
  int level(const Protocol& protocol) const
  {
    if (protocol.family() == PF_INET6)
      return IPv6_Level;
    return IPv4_Level;
  }

  template <typename Protocol>
  int name(const Protocol& protocol) const
  {
    if (protocol.family() == PF_INET6)
      return IPv6_Name;
    return IPv4_Name;
  }

  template <typename Protocol>
  void* data(const Protocol& protocol)
  {
    if (protocol.family() == PF_INET6)
      return &ipv6_value_;
    return &ipv4_value_;
  }

  template <typename Protocol>
  const void* data(const Protocol& protocol) const
  {
    if (protocol.family() == PF_INET6)
      return &ipv6_value_;
    return &ipv4_value_;
  }

  template <typename Protocol>
  std::size_t size(const Protocol& protocol) const
  {
    if (protocol.family() == PF_INET6)
      return sizeof(ipv6_value_);
    return sizeof(ipv4_value_);
  }

  template <typename Protocol>
  void resize(const Protocol& protocol, std::size_t s)
  {
    if (protocol.family() == PF_INET6)
    {
      if (s != sizeof(ipv6_value_))
      {
        std::length_error ex("multicast_enable_loopback socket option resize");
        boost::asio::detail::throw_exception(ex);
      }
      ipv4_value_ = ipv6_value_ ? 1 : 0;
    }
    else
    {
      if (s != sizeof(ipv4_value_))
      {
        std::length_error ex("multicast_enable_loopback socket option resize");
        boost::asio::detail::throw_exception(ex);
      }
      ipv6_value_ = ipv4_value_ ? 1 : 0;
    }
  }

  unicast_hops()
    : value_(0)
  {
  }

  explicit unicast_hops(int v)
    : value_(v)
  {
  }

  unicast_hops& operator=(int v)
  {
    value_ = v;
    return *this;
  }

  int value() const
  {
    return value_;
  }

  template <typename Protocol>
  int level(const Protocol& protocol) const
  {
    if (protocol.family() == PF_INET6)
      return IPv6_Level;
    return IPv4_Level;
  }

  template <typename Protocol>
  int name(const Protocol& protocol) const
  {
    if (protocol.family() == PF_INET6)
      return IPv6_Name;
    return IPv4_Name;
  }

  template <typename Protocol>
  int* data(const Protocol&)
  {
    return &value_;
  }

  template <typename Protocol>
  const int* data(const Protocol&) const
  {
    return &value_;
  }

  template <typename Protocol>
  std::size_t size(const Protocol&) const
  {
    return sizeof(value_);
  }

  template <typename Protocol>
  void resize(const Protocol&, std::size_t s)
  {
    if (s != sizeof(value_))
    {
      std::length_error ex("unicast hops socket option resize");
      boost::asio::detail::throw_exception(ex);
    }
#if defined(__hpux)
    if (value_ < 0)
      value_ = value_ & 0xFF;
#endif
  }

  multicast_hops()
    : ipv4_value_(0),
      ipv6_value_(0)
  {
  }

  explicit multicast_hops(int v)
  {
    if (v < 0 || v > 255)
    {
      std::out_of_range ex("multicast hops value out of range");
      boost::asio::detail::throw_exception(ex);
    }
    ipv4_value_ = (ipv4_value_type)v;
    ipv6_value_ = v;
  }

  multicast_hops& operator=(int v)
  {
    if (v < 0 || v > 255)
    {
      std::out_of_range ex("multicast hops value out of range");
      boost::asio::detail::throw_exception(ex);
    }
    ipv4_value_ = (ipv4_value_type)v;
    ipv6_value_ = v;
    return *this;
  }

  int value() const
  {
    return ipv6_value_;
  }

  template <typename Protocol>
  int level(const Protocol& protocol) const
  {
    if (protocol.family() == PF_INET6)
      return IPv6_Level;
    return IPv4_Level;
  }

  template <typename Protocol>
  int name(const Protocol& protocol) const
  {
    if (protocol.family() == PF_INET6)
      return IPv6_Name;
    return IPv4_Name;
  }

  template <typename Protocol>
  void* data(const Protocol& protocol)
  {
    if (protocol.family() == PF_INET6)
      return &ipv6_value_;
    return &ipv4_value_;
  }

  template <typename Protocol>
  const void* data(const Protocol& protocol) const
  {
    if (protocol.family() == PF_INET6)
      return &ipv6_value_;
    return &ipv4_value_;
  }

  template <typename Protocol>
  std::size_t size(const Protocol& protocol) const
  {
    if (protocol.family() == PF_INET6)
      return sizeof(ipv6_value_);
    return sizeof(ipv4_value_);
  }

  template <typename Protocol>
  void resize(const Protocol& protocol, std::size_t s)
  {
    if (protocol.family() == PF_INET6)
    {
      if (s != sizeof(ipv6_value_))
      {
        std::length_error ex("multicast hops socket option resize");
        boost::asio::detail::throw_exception(ex);
      }
      if (ipv6_value_ < 0)
        ipv4_value_ = 0;
      else if (ipv6_value_ > 255)
        ipv4_value_ = 255;
      else
        ipv4_value_ = (ipv4_value_type)ipv6_value_;
    }
    else
    {
      if (s != sizeof(ipv4_value_))
      {
        std::length_error ex("multicast hops socket option resize");
        boost::asio::detail::throw_exception(ex);
      }
      ipv6_value_ = ipv4_value_;
    }
  }

  multicast_request()
    : ipv4_value_(), // Zero-initialisation gives the "any" address.
      ipv6_value_() // Zero-initialisation gives the "any" address.
  {
  }

  template <typename Protocol>
  int level(const Protocol& protocol) const
  {
    if (protocol.family() == PF_INET6)
      return IPv6_Level;
    return IPv4_Level;
  }

  template <typename Protocol>
  int name(const Protocol& protocol) const
  {
    if (protocol.family() == PF_INET6)
      return IPv6_Name;
    return IPv4_Name;
  }

  template <typename Protocol>
  const void* data(const Protocol& protocol) const
  {
    if (protocol.family() == PF_INET6)
      return &ipv6_value_;
    return &ipv4_value_;
  }

  template <typename Protocol>
  std::size_t size(const Protocol& protocol) const
  {
    if (protocol.family() == PF_INET6)
      return sizeof(ipv6_value_);
    return sizeof(ipv4_value_);
  }

  network_interface()
  {
    ipv4_value_.s_addr =
      boost::asio::detail::socket_ops::host_to_network_long(
          boost::asio::ip::address_v4::any().to_ulong());
    ipv6_value_ = 0;
  }

  explicit network_interface(unsigned int ipv6_interface)
  {
    ipv4_value_.s_addr =
      boost::asio::detail::socket_ops::host_to_network_long(
          boost::asio::ip::address_v4::any().to_ulong());
    ipv6_value_ = ipv6_interface;
  }

  template <typename Protocol>
  int level(const Protocol& protocol) const
  {
    if (protocol.family() == PF_INET6)
      return IPv6_Level;
    return IPv4_Level;
  }

  template <typename Protocol>
  int name(const Protocol& protocol) const
  {
    if (protocol.family() == PF_INET6)
      return IPv6_Name;
    return IPv4_Name;
  }

  template <typename Protocol>
  const void* data(const Protocol& protocol) const
  {
    if (protocol.family() == PF_INET6)
      return &ipv6_value_;
    return &ipv4_value_;
  }

  template <typename Protocol>
  std::size_t size(const Protocol& protocol) const
  {
    if (protocol.family() == PF_INET6)
      return sizeof(ipv6_value_);
    return sizeof(ipv4_value_);
  }

  basic_endpoint()
  {
  }

  template <typename Endpoint>
  basic_endpoint(const Endpoint& endpoint)
    : impl_(endpoint.data(), endpoint.size(), endpoint.protocol().protocol())
  {
  }

  basic_endpoint(const basic_endpoint& other)
    : impl_(other.impl_)
  {
  }

  basic_endpoint& operator=(const basic_endpoint& other)
  {
    impl_ = other.impl_;
    return *this;
  }

  protocol_type protocol() const
  {
    return protocol_type(impl_.family(), impl_.protocol());
  }

  data_type* data()
  {
    return impl_.data();
  }

  const data_type* data() const
  {
    return impl_.data();
  }

  std::size_t size() const
  {
    return impl_.size();
  }

  void resize(std::size_t new_size)
  {
    impl_.resize(new_size);
  }

  std::size_t capacity() const
  {
    return impl_.capacity();
  }

  seq_packet_protocol(int address_family, int socket_protocol)
    : family_(address_family),
      protocol_(socket_protocol)
  {
  }

  template <typename Protocol>
  seq_packet_protocol(const Protocol& source_protocol)
    : family_(source_protocol.family()),
      protocol_(source_protocol.protocol())
  {
    if (source_protocol.type() != type())
    {
      std::bad_cast ex;
      boost::asio::detail::throw_exception(ex);
    }
  }

  int type() const
  {
    return SOCK_SEQPACKET;
  }

  int protocol() const
  {
    return protocol_;
  }

  int family() const
  {
    return family_;
  }

  raw_protocol(int address_family, int socket_protocol)
    : family_(address_family),
      protocol_(socket_protocol)
  {
  }

  template <typename Protocol>
  raw_protocol(const Protocol& source_protocol)
    : family_(source_protocol.family()),
      protocol_(source_protocol.protocol())
  {
    if (source_protocol.type() != type())
    {
      std::bad_cast ex;
      boost::asio::detail::throw_exception(ex);
    }
  }

  int type() const
  {
    return SOCK_RAW;
  }

  int protocol() const
  {
    return protocol_;
  }

  int family() const
  {
    return family_;
  }

  datagram_protocol(int address_family, int socket_protocol)
    : family_(address_family),
      protocol_(socket_protocol)
  {
  }

  template <typename Protocol>
  datagram_protocol(const Protocol& source_protocol)
    : family_(source_protocol.family()),
      protocol_(source_protocol.protocol())
  {
    if (source_protocol.type() != type())
    {
      std::bad_cast ex;
      boost::asio::detail::throw_exception(ex);
    }
  }

  int type() const
  {
    return SOCK_DGRAM;
  }

  int protocol() const
  {
    return protocol_;
  }

  int family() const
  {
    return family_;
  }

  stream_protocol(int address_family, int socket_protocol)
    : family_(address_family),
      protocol_(socket_protocol)
  {
  }

  template <typename Protocol>
  stream_protocol(const Protocol& source_protocol)
    : family_(source_protocol.family()),
      protocol_(source_protocol.protocol())
  {
    if (source_protocol.type() != type())
    {
      std::bad_cast ex;
      boost::asio::detail::throw_exception(ex);
    }
  }

  int type() const
  {
    return SOCK_STREAM;
  }

  int protocol() const
  {
    return protocol_;
  }

  int family() const
  {
    return family_;
  }

  endpoint(const endpoint& other)
    : data_(other.data_),
      size_(other.size_),
      protocol_(other.protocol_)
  {
  }

  endpoint& operator=(const endpoint& other)
  {
    data_ = other.data_;
    size_ = other.size_;
    protocol_ = other.protocol_;
    return *this;
  }

  int family() const
  {
    return data_.base.sa_family;
  }

  int protocol() const
  {
    return protocol_;
  }

  boost::asio::detail::socket_addr_type* data()
  {
    return &data_.base;
  }

  std::size_t size() const
  {
    return size_;
  }

  std::size_t capacity() const
  {
    return sizeof(boost::asio::detail::sockaddr_storage_type);
  }

  reactive_socket_sendto_op_base(socket_type socket,
      const ConstBufferSequence& buffers, const Endpoint& endpoint,
      socket_base::message_flags flags, func_type complete_func)
    : reactor_op(&reactive_socket_sendto_op_base::do_perform, complete_func),
      socket_(socket),
      buffers_(buffers),
      destination_(endpoint),
      flags_(flags)
  {
  }


  static bool do_perform(reactor_op* base)
  {
    reactive_socket_sendto_op_base* o(
        static_cast<reactive_socket_sendto_op_base*>(base));

    buffer_sequence_adapter<boost::asio::const_buffer,
        ConstBufferSequence> bufs(o->buffers_);

    return socket_ops::non_blocking_sendto(o->socket_,
          bufs.buffers(), bufs.count(), o->flags_,
          o->destination_.data(), o->destination_.size(),
          o->ec_, o->bytes_transferred_);
  }


  reactive_socket_sendto_op(socket_type socket,
      const ConstBufferSequence& buffers, const Endpoint& endpoint,
      socket_base::message_flags flags, Handler& handler)
    : reactive_socket_sendto_op_base<ConstBufferSequence, Endpoint>(socket,
        buffers, endpoint, flags, &reactive_socket_sendto_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler))
  {
  }


  static void do_complete(io_service_impl* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    reactive_socket_sendto_op* o(static_cast<reactive_socket_sendto_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };

    BOOST_ASIO_HANDLER_COMPLETION((o));

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder2<Handler, boost::system::error_code, std::size_t>
      handler(o->handler_, o->ec_, o->bytes_transferred_);
    p.h = boost::asio::detail::addressof(handler.handler_);
    p.reset();

    // Make the upcall if required.
    if (owner)
    {
      fenced_block b(fenced_block::half);
      BOOST_ASIO_HANDLER_INVOCATION_BEGIN((handler.arg1_, handler.arg2_));
      boost_asio_handler_invoke_helpers::invoke(handler, handler.handler_);
      BOOST_ASIO_HANDLER_INVOCATION_END;
    }
  }

    implementation_type()
      : protocol_(endpoint_type().protocol())
    {
    }

  reactive_socket_service(boost::asio::io_service& io_service)
    : reactive_socket_service_base(io_service)
  {
  }

  void move_construct(implementation_type& impl,
      implementation_type& other_impl)
  {
    this->base_move_construct(impl, other_impl);

    impl.protocol_ = other_impl.protocol_;
    other_impl.protocol_ = endpoint_type().protocol();
  }

  void move_assign(implementation_type& impl,
      reactive_socket_service_base& other_service,
      implementation_type& other_impl)
  {
    this->base_move_assign(impl, other_service, other_impl);

    impl.protocol_ = other_impl.protocol_;
    other_impl.protocol_ = endpoint_type().protocol();
  }

  template <typename Protocol1>
  void converting_move_construct(implementation_type& impl,
      typename reactive_socket_service<
        Protocol1>::implementation_type& other_impl)
  {
    this->base_move_construct(impl, other_impl);

    impl.protocol_ = protocol_type(other_impl.protocol_);
    other_impl.protocol_ = typename Protocol1::endpoint().protocol();
  }

  boost::system::error_code open(implementation_type& impl,
      const protocol_type& protocol, boost::system::error_code& ec)
  {
    if (!do_open(impl, protocol.family(),
          protocol.type(), protocol.protocol(), ec))
      impl.protocol_ = protocol;
    return ec;
  }

  boost::system::error_code assign(implementation_type& impl,
      const protocol_type& protocol, const native_handle_type& native_socket,
      boost::system::error_code& ec)
  {
    if (!do_assign(impl, protocol.type(), native_socket, ec))
      impl.protocol_ = protocol;
    return ec;
  }

  native_handle_type native_handle(implementation_type& impl)
  {
    return impl.socket_;
  }

  boost::system::error_code bind(implementation_type& impl,
      const endpoint_type& endpoint, boost::system::error_code& ec)
  {
    socket_ops::bind(impl.socket_, endpoint.data(), endpoint.size(), ec);
    return ec;
  }

  template <typename Option>
  boost::system::error_code set_option(implementation_type& impl,
      const Option& option, boost::system::error_code& ec)
  {
    socket_ops::setsockopt(impl.socket_, impl.state_,
        option.level(impl.protocol_), option.name(impl.protocol_),
        option.data(impl.protocol_), option.size(impl.protocol_), ec);
    return ec;
  }

  template <typename Option>
  boost::system::error_code get_option(const implementation_type& impl,
      Option& option, boost::system::error_code& ec) const
  {
    std::size_t size = option.size(impl.protocol_);
    socket_ops::getsockopt(impl.socket_, impl.state_,
        option.level(impl.protocol_), option.name(impl.protocol_),
        option.data(impl.protocol_), &size, ec);
    if (!ec)
      option.resize(impl.protocol_, size);
    return ec;
  }

  endpoint_type local_endpoint(const implementation_type& impl,
      boost::system::error_code& ec) const
  {
    endpoint_type endpoint;
    std::size_t addr_len = endpoint.capacity();
    if (socket_ops::getsockname(impl.socket_, endpoint.data(), &addr_len, ec))
      return endpoint_type();
    endpoint.resize(addr_len);
    return endpoint;
  }

  endpoint_type remote_endpoint(const implementation_type& impl,
      boost::system::error_code& ec) const
  {
    endpoint_type endpoint;
    std::size_t addr_len = endpoint.capacity();
    if (socket_ops::getpeername(impl.socket_,
          endpoint.data(), &addr_len, false, ec))
      return endpoint_type();
    endpoint.resize(addr_len);
    return endpoint;
  }

  template <typename ConstBufferSequence>
  size_t send_to(implementation_type& impl, const ConstBufferSequence& buffers,
      const endpoint_type& destination, socket_base::message_flags flags,
      boost::system::error_code& ec)
  {
    buffer_sequence_adapter<boost::asio::const_buffer,
        ConstBufferSequence> bufs(buffers);

    return socket_ops::sync_sendto(impl.socket_, impl.state_,
        bufs.buffers(), bufs.count(), flags,
        destination.data(), destination.size(), ec);
  }

  template <typename ConstBufferSequence, typename Handler>
  void async_send_to(implementation_type& impl,
      const ConstBufferSequence& buffers,
      const endpoint_type& destination, socket_base::message_flags flags,
      Handler& handler)
  {
    bool is_continuation =
      boost_asio_handler_cont_helpers::is_continuation(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef reactive_socket_sendto_op<ConstBufferSequence,
        endpoint_type, Handler> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      boost_asio_handler_alloc_helpers::allocate(
        sizeof(op), handler), 0 };
    p.p = new (p.v) op(impl.socket_, buffers, destination, flags, handler);

    BOOST_ASIO_HANDLER_CREATION((p.p, "socket", &impl, "async_send_to"));

    start_op(impl, reactor::write_op, p.p, is_continuation, true, false);
    p.v = p.p = 0;
  }

  template <typename MutableBufferSequence>
  size_t receive_from(implementation_type& impl,
      const MutableBufferSequence& buffers,
      endpoint_type& sender_endpoint, socket_base::message_flags flags,
      boost::system::error_code& ec)
  {
    buffer_sequence_adapter<boost::asio::mutable_buffer,
        MutableBufferSequence> bufs(buffers);

    std::size_t addr_len = sender_endpoint.capacity();
    std::size_t bytes_recvd = socket_ops::sync_recvfrom(
        impl.socket_, impl.state_, bufs.buffers(), bufs.count(),
        flags, sender_endpoint.data(), &addr_len, ec);

    if (!ec)
      sender_endpoint.resize(addr_len);

    return bytes_recvd;
  }

  template <typename MutableBufferSequence, typename Handler>
  void async_receive_from(implementation_type& impl,
      const MutableBufferSequence& buffers, endpoint_type& sender_endpoint,
      socket_base::message_flags flags, Handler& handler)
  {
    bool is_continuation =
      boost_asio_handler_cont_helpers::is_continuation(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef reactive_socket_recvfrom_op<MutableBufferSequence,
        endpoint_type, Handler> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      boost_asio_handler_alloc_helpers::allocate(
        sizeof(op), handler), 0 };
    int protocol = impl.protocol_.type();
    p.p = new (p.v) op(impl.socket_, protocol,
        buffers, sender_endpoint, flags, handler);

    BOOST_ASIO_HANDLER_CREATION((p.p, "socket",
          &impl, "async_receive_from"));

    start_op(impl,
        (flags & socket_base::message_out_of_band)
          ? reactor::except_op : reactor::read_op,
        p.p, is_continuation, true, false);
    p.v = p.p = 0;
  }

  template <typename Socket>
  boost::system::error_code accept(implementation_type& impl,
      Socket& peer, endpoint_type* peer_endpoint, boost::system::error_code& ec)
  {
    // We cannot accept a socket that is already open.
    if (peer.is_open())
    {
      ec = boost::asio::error::already_open;
      return ec;
    }

    std::size_t addr_len = peer_endpoint ? peer_endpoint->capacity() : 0;
    socket_holder new_socket(socket_ops::sync_accept(impl.socket_,
          impl.state_, peer_endpoint ? peer_endpoint->data() : 0,
          peer_endpoint ? &addr_len : 0, ec));

    // On success, assign new connection to peer socket object.
    if (new_socket.get() != invalid_socket)
    {
      if (peer_endpoint)
        peer_endpoint->resize(addr_len);
      if (!peer.assign(impl.protocol_, new_socket.get(), ec))
        new_socket.release();
    }

    return ec;
  }

  template <typename Socket, typename Handler>
  void async_accept(implementation_type& impl, Socket& peer,
      endpoint_type* peer_endpoint, Handler& handler)
  {
    bool is_continuation =
      boost_asio_handler_cont_helpers::is_continuation(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef reactive_socket_accept_op<Socket, Protocol, Handler> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      boost_asio_handler_alloc_helpers::allocate(
        sizeof(op), handler), 0 };
    p.p = new (p.v) op(impl.socket_, impl.state_, peer,
        impl.protocol_, peer_endpoint, handler);

    BOOST_ASIO_HANDLER_CREATION((p.p, "socket", &impl, "async_accept"));

    start_accept_op(impl, p.p, is_continuation, peer.is_open());
    p.v = p.p = 0;
  }

  boost::system::error_code connect(implementation_type& impl,
      const endpoint_type& peer_endpoint, boost::system::error_code& ec)
  {
    socket_ops::sync_connect(impl.socket_,
        peer_endpoint.data(), peer_endpoint.size(), ec);
    return ec;
  }

  template <typename Handler>
  void async_connect(implementation_type& impl,
      const endpoint_type& peer_endpoint, Handler& handler)
  {
    bool is_continuation =
      boost_asio_handler_cont_helpers::is_continuation(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef reactive_socket_connect_op<Protocol, Handler> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      boost_asio_handler_alloc_helpers::allocate(
        sizeof(op), handler), 0 };
    p.p = new (p.v) op(impl.socket_, peer_endpoint, handler);

    BOOST_ASIO_HANDLER_CREATION((p.p, "socket", &impl, "async_connect"));

    start_connect_op(impl, p.p, is_continuation,
        peer_endpoint.data(), peer_endpoint.size());
    p.v = p.p = 0;
  }

template <typename Exception>
void throw_exception(const Exception& e)
{
  throw e;
}

  explicit scoped_ptr(T* p = 0)
    : p_(p)
  {
  }

  ~scoped_ptr()
  {
    delete p_;
  }

  T* get()
  {
    return p_;
  }

  T* operator->()
  {
    return p_;
  }

  T& operator*()
  {
    return *p_;
  }

  void reset(T* p = 0)
  {
    delete p_;
    p_ = p;
  }

  void operator=(T* value)
  {
#if !defined(BOOST_ASIO_HAS_THREADS)
    null_tss_ptr<T>::operator=(value);
#elif defined(BOOST_ASIO_HAS_THREAD_KEYWORD_EXTENSION)
    keyword_tss_ptr<T>::operator=(value);
#elif defined(BOOST_ASIO_WINDOWS)
    win_tss_ptr<T>::operator=(value);
#elif defined(BOOST_ASIO_HAS_PTHREADS)
    posix_tss_ptr<T>::operator=(value);
#endif
  }

  wait_op(func_type func)
    : operation(func)
  {
  }

  explicit buffered_stream_storage(std::size_t buffer_capacity)
    : begin_offset_(0),
      end_offset_(0),
      buffer_(buffer_capacity)
  {
  }

  void clear()
  {
    begin_offset_ = 0;
    end_offset_ = 0;
  }

  mutable_buffer data()
  {
    return boost::asio::buffer(buffer_) + begin_offset_;
  }

  bool empty() const
  {
    return begin_offset_ == end_offset_;
  }

  size_type size() const
  {
    return end_offset_ - begin_offset_;
  }

  void resize(size_type length)
  {
    BOOST_ASIO_ASSERT(length <= capacity());
    if (begin_offset_ + length <= capacity())
    {
      end_offset_ = begin_offset_ + length;
    }
    else
    {
      using namespace std; // For memmove.
      memmove(&buffer_[0], &buffer_[0] + begin_offset_, size());
      end_offset_ = length;
      begin_offset_ = 0;
    }
  }

  size_type capacity() const
  {
    return buffer_.size();
  }

  void consume(size_type count)
  {
    BOOST_ASIO_ASSERT(begin_offset_ + count <= end_offset_);
    begin_offset_ += count;
    if (empty())
      clear();
  }

  deadline_timer_service(boost::asio::io_service& io_service)
    : scheduler_(boost::asio::use_service<timer_scheduler>(io_service))
  {
    scheduler_.init_task();
    scheduler_.add_timer_queue(timer_queue_);
  }

  ~deadline_timer_service()
  {
    scheduler_.remove_timer_queue(timer_queue_);
  }

  void shutdown_service()
  {
  }

  void construct(implementation_type& impl)
  {
    impl.expiry = time_type();
    impl.might_have_pending_waits = false;
  }

  void destroy(implementation_type& impl)
  {
    boost::system::error_code ec;
    cancel(impl, ec);
  }

  std::size_t cancel(implementation_type& impl, boost::system::error_code& ec)
  {
    if (!impl.might_have_pending_waits)
    {
      ec = boost::system::error_code();
      return 0;
    }

    BOOST_ASIO_HANDLER_OPERATION(("deadline_timer", &impl, "cancel"));

    std::size_t count = scheduler_.cancel_timer(timer_queue_, impl.timer_data);
    impl.might_have_pending_waits = false;
    ec = boost::system::error_code();
    return count;
  }

  std::size_t cancel_one(implementation_type& impl,
      boost::system::error_code& ec)
  {
    if (!impl.might_have_pending_waits)
    {
      ec = boost::system::error_code();
      return 0;
    }

    BOOST_ASIO_HANDLER_OPERATION(("deadline_timer", &impl, "cancel_one"));

    std::size_t count = scheduler_.cancel_timer(
        timer_queue_, impl.timer_data, 1);
    if (count == 0)
      impl.might_have_pending_waits = false;
    ec = boost::system::error_code();
    return count;
  }

  time_type expires_at(const implementation_type& impl) const
  {
    return impl.expiry;
  }

  duration_type expires_from_now(const implementation_type& impl) const
  {
    return Time_Traits::subtract(expires_at(impl), Time_Traits::now());
  }

  void wait(implementation_type& impl, boost::system::error_code& ec)
  {
    time_type now = Time_Traits::now();
    ec = boost::system::error_code();
    while (Time_Traits::less_than(now, impl.expiry) && !ec)
    {
      this->do_wait(Time_Traits::to_posix_duration(
            Time_Traits::subtract(impl.expiry, now)), ec);
      now = Time_Traits::now();
    }
  }

  template <typename Handler>
  void async_wait(implementation_type& impl, Handler& handler)
  {
    // Allocate and construct an operation to wrap the handler.
    typedef wait_handler<Handler> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      boost_asio_handler_alloc_helpers::allocate(
        sizeof(op), handler), 0 };
    p.p = new (p.v) op(handler);

    impl.might_have_pending_waits = true;

    BOOST_ASIO_HANDLER_CREATION((p.p, "deadline_timer", &impl, "async_wait"));

    scheduler_.schedule_timer(timer_queue_, impl.expiry, impl.timer_data, p.p);
    p.v = p.p = 0;
  }

  template <typename Duration>
  void do_wait(const Duration& timeout, boost::system::error_code& ec)
  {
    ::timeval tv;
    tv.tv_sec = timeout.total_seconds();
    tv.tv_usec = timeout.total_microseconds() % 1000000;
    socket_ops::select(0, 0, 0, 0, &tv, ec);
  }

  consuming_buffers_iterator()
    : at_end_(true)
  {
  }

  const Buffer& operator*() const
  {
    return dereference();
  }

  const Buffer* operator->() const
  {
    return &dereference();
  }

  consuming_buffers_iterator& operator++()
  {
    increment();
    return *this;
  }

  consuming_buffers_iterator operator++(int)
  {
    consuming_buffers_iterator tmp(*this);
    ++*this;
    return tmp;
  }

  void increment()
  {
    if (!at_end_)
    {
      if (begin_remainder_ == end_remainder_
          || offset_ + buffer_size(first_) >= max_size_)
      {
        at_end_ = true;
      }
      else
      {
        offset_ += buffer_size(first_);
        first_ = buffer(*begin_remainder_++, max_size_ - offset_);
      }
    }
  }


  bool equal(const consuming_buffers_iterator& other) const
  {
    if (at_end_ && other.at_end_)
      return true;
    return !at_end_ && !other.at_end_
      && buffer_cast<const void*>(first_)
        == buffer_cast<const void*>(other.first_)
      && buffer_size(first_) == buffer_size(other.first_)
      && begin_remainder_ == other.begin_remainder_
      && end_remainder_ == other.end_remainder_;
  }


  const Buffer& dereference() const
  {
    return first_;
  }

  consuming_buffers(const Buffers& buffers)
    : buffers_(buffers),
      at_end_(buffers_.begin() == buffers_.end()),
      begin_remainder_(buffers_.begin()),
      max_size_((std::numeric_limits<std::size_t>::max)())
  {
    if (!at_end_)
    {
      first_ = *buffers_.begin();
      ++begin_remainder_;
    }
  }

  consuming_buffers(const consuming_buffers& other)
    : buffers_(other.buffers_),
      at_end_(other.at_end_),
      first_(other.first_),
      begin_remainder_(buffers_.begin()),
      max_size_(other.max_size_)
  {
    typename Buffers::const_iterator first = other.buffers_.begin();
    typename Buffers::const_iterator second = other.begin_remainder_;
    std::advance(begin_remainder_, std::distance(first, second));
  }

  consuming_buffers& operator=(const consuming_buffers& other)
  {
    buffers_ = other.buffers_;
    at_end_ = other.at_end_;
    first_ = other.first_;
    begin_remainder_ = buffers_.begin();
    typename Buffers::const_iterator first = other.buffers_.begin();
    typename Buffers::const_iterator second = other.begin_remainder_;
    std::advance(begin_remainder_, std::distance(first, second));
    max_size_ = other.max_size_;
    return *this;
  }

  const_iterator begin() const
  {
    return const_iterator(at_end_, first_,
        begin_remainder_, buffers_.end(), max_size_);
  }

  const_iterator end() const
  {
    return const_iterator();
  }

  void prepare(std::size_t max_size)
  {
    max_size_ = max_size;
  }

  void consume(std::size_t size)
  {
    // Remove buffers from the start until the specified size is reached.
    while (size > 0 && !at_end_)
    {
      if (buffer_size(first_) <= size)
      {
        size -= buffer_size(first_);
        if (begin_remainder_ == buffers_.end())
          at_end_ = true;
        else
          first_ = *begin_remainder_++;
      }
      else
      {
        first_ = first_ + size;
        size = 0;
      }
    }

    // Remove any more empty buffers at the start.
    while (!at_end_ && buffer_size(first_) == 0)
    {
      if (begin_remainder_ == buffers_.end())
        at_end_ = true;
      else
        first_ = *begin_remainder_++;
    }
  }

  reactive_socket_accept_op_base(socket_type socket,
      socket_ops::state_type state, Socket& peer, const Protocol& protocol,
      typename Protocol::endpoint* peer_endpoint, func_type complete_func)
    : reactor_op(&reactive_socket_accept_op_base::do_perform, complete_func),
      socket_(socket),
      state_(state),
      peer_(peer),
      protocol_(protocol),
      peer_endpoint_(peer_endpoint)
  {
  }


  static bool do_perform(reactor_op* base)
  {
    reactive_socket_accept_op_base* o(
        static_cast<reactive_socket_accept_op_base*>(base));

    std::size_t addrlen = o->peer_endpoint_ ? o->peer_endpoint_->capacity() : 0;
    socket_type new_socket = invalid_socket;
    bool result = socket_ops::non_blocking_accept(o->socket_,
          o->state_, o->peer_endpoint_ ? o->peer_endpoint_->data() : 0,
          o->peer_endpoint_ ? &addrlen : 0, o->ec_, new_socket);

    // On success, assign new connection to peer socket object.
    if (new_socket >= 0)
    {
      socket_holder new_socket_holder(new_socket);
      if (o->peer_endpoint_)
        o->peer_endpoint_->resize(addrlen);
      if (!o->peer_.assign(o->protocol_, new_socket, o->ec_))
        new_socket_holder.release();
    }

    return result;
  }


  reactive_socket_accept_op(socket_type socket,
      socket_ops::state_type state, Socket& peer, const Protocol& protocol,
      typename Protocol::endpoint* peer_endpoint, Handler& handler)
    : reactive_socket_accept_op_base<Socket, Protocol>(socket, state, peer,
        protocol, peer_endpoint, &reactive_socket_accept_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler))
  {
  }


  static void do_complete(io_service_impl* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    reactive_socket_accept_op* o(static_cast<reactive_socket_accept_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };

    BOOST_ASIO_HANDLER_COMPLETION((o));

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder1<Handler, boost::system::error_code>
      handler(o->handler_, o->ec_);
    p.h = boost::asio::detail::addressof(handler.handler_);
    p.reset();

    // Make the upcall if required.
    if (owner)
    {
      fenced_block b(fenced_block::half);
      BOOST_ASIO_HANDLER_INVOCATION_BEGIN((handler.arg1_));
      boost_asio_handler_invoke_helpers::invoke(handler, handler.handler_);
      BOOST_ASIO_HANDLER_INVOCATION_END;
    }
  }


  wait_handler(Handler& h)
    : wait_op(&wait_handler::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(h))
  {
  }


  static void do_complete(io_service_impl* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    wait_handler* h(static_cast<wait_handler*>(base));
    ptr p = { boost::asio::detail::addressof(h->handler_), h, h };

    BOOST_ASIO_HANDLER_COMPLETION((h));

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder1<Handler, boost::system::error_code>
      handler(h->handler_, h->ec_);
    p.h = boost::asio::detail::addressof(handler.handler_);
    p.reset();

    // Make the upcall if required.
    if (owner)
    {
      fenced_block b(fenced_block::half);
      BOOST_ASIO_HANDLER_INVOCATION_BEGIN((handler.arg1_));
      boost_asio_handler_invoke_helpers::invoke(handler, handler.handler_);
      BOOST_ASIO_HANDLER_INVOCATION_END;
    }
  }

  posix_fd_set_adapter()
    : max_descriptor_(invalid_socket)
  {
    using namespace std; // Needed for memset on Solaris.
    FD_ZERO(&fd_set_);
  }


  void reset()
  {
    using namespace std; // Needed for memset on Solaris.
    FD_ZERO(&fd_set_);
  }


  bool set(socket_type descriptor)
  {
    if (descriptor < (socket_type)FD_SETSIZE)
    {
      if (max_descriptor_ == invalid_socket || descriptor > max_descriptor_)
        max_descriptor_ = descriptor;
      FD_SET(descriptor, &fd_set_);
      return true;
    }
    return false;
  }


  bool is_set(socket_type descriptor) const
  {
    return FD_ISSET(descriptor, &fd_set_) != 0;
  }


inline std::size_t calculate_hash_value(int i)
{
  return static_cast<std::size_t>(i);
}

  hash_map()
    : size_(0),
      buckets_(0),
      num_buckets_(0)
  {
  }

  ~hash_map()
  {
    delete[] buckets_;
  }

  iterator begin()
  {
    return values_.begin();
  }

  iterator end()
  {
    return values_.end();
  }

  bool empty() const
  {
    return values_.empty();
  }

  iterator find(const K& k)
  {
    if (num_buckets_)
    {
      size_t bucket = calculate_hash_value(k) % num_buckets_;
      iterator it = buckets_[bucket].first;
      if (it == values_.end())
        return values_.end();
      iterator end_it = buckets_[bucket].last;
      ++end_it;
      while (it != end_it)
      {
        if (it->first == k)
          return it;
        ++it;
      }
    }
    return values_.end();
  }

    registration()
      : signal_number_(0),
        queue_(0),
        undelivered_(0),
        next_in_table_(0),
        prev_in_table_(0),
        next_in_set_(0)
    {
    }

    implementation_type()
      : signals_(0)
    {
    }

  template <typename Handler>
  void async_wait(implementation_type& impl, Handler& handler)
  {
    // Allocate and construct an operation to wrap the handler.
    typedef signal_handler<Handler> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      boost_asio_handler_alloc_helpers::allocate(
        sizeof(op), handler), 0 };
    p.p = new (p.v) op(handler);

    BOOST_ASIO_HANDLER_CREATION((p.p, "signal_set", &impl, "async_wait"));

    start_wait_op(impl, p.p);
    p.v = p.p = 0;
  }

  null_tss_ptr()
    : value_(0)
  {
  }

  ~null_tss_ptr()
  {
  }

  operator T*() const
  {
    return value_;
  }

  void operator=(T* value)
  {
    value_ = value;
  }
 void operator()(void*) {}

  reactive_socket_recvmsg_op_base(socket_type socket,
      const MutableBufferSequence& buffers, socket_base::message_flags in_flags,
      socket_base::message_flags& out_flags, func_type complete_func)
    : reactor_op(&reactive_socket_recvmsg_op_base::do_perform, complete_func),
      socket_(socket),
      buffers_(buffers),
      in_flags_(in_flags),
      out_flags_(out_flags)
  {
  }


  static bool do_perform(reactor_op* base)
  {
    reactive_socket_recvmsg_op_base* o(
        static_cast<reactive_socket_recvmsg_op_base*>(base));

    buffer_sequence_adapter<boost::asio::mutable_buffer,
        MutableBufferSequence> bufs(o->buffers_);

    return socket_ops::non_blocking_recvmsg(o->socket_,
        bufs.buffers(), bufs.count(),
        o->in_flags_, o->out_flags_,
        o->ec_, o->bytes_transferred_);
  }


  reactive_socket_recvmsg_op(socket_type socket,
      const MutableBufferSequence& buffers, socket_base::message_flags in_flags,
      socket_base::message_flags& out_flags, Handler& handler)
    : reactive_socket_recvmsg_op_base<MutableBufferSequence>(socket, buffers,
        in_flags, out_flags, &reactive_socket_recvmsg_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler))
  {
  }


  static void do_complete(io_service_impl* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    reactive_socket_recvmsg_op* o(
        static_cast<reactive_socket_recvmsg_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };

    BOOST_ASIO_HANDLER_COMPLETION((o));

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder2<Handler, boost::system::error_code, std::size_t>
      handler(o->handler_, o->ec_, o->bytes_transferred_);
    p.h = boost::asio::detail::addressof(handler.handler_);
    p.reset();

    // Make the upcall if required.
    if (owner)
    {
      fenced_block b(fenced_block::half);
      BOOST_ASIO_HANDLER_INVOCATION_BEGIN((handler.arg1_, handler.arg2_));
      boost_asio_handler_invoke_helpers::invoke(handler, handler.handler_);
      BOOST_ASIO_HANDLER_INVOCATION_END;
    }
  }

  null_signal_blocker()
  {
  }

  ~null_signal_blocker()
  {
  }

  void block()
  {
  }

  void unblock()
  {
  }

inline void increment(atomic_count& a, long b) { a += b; }

  bool is_open(const base_implementation_type& impl) const
  {
    return impl.socket_ != invalid_socket;
  }

  native_handle_type native_handle(base_implementation_type& impl)
  {
    return impl.socket_;
  }

  bool at_mark(const base_implementation_type& impl,
      boost::system::error_code& ec) const
  {
    return socket_ops::sockatmark(impl.socket_, ec);
  }

  std::size_t available(const base_implementation_type& impl,
      boost::system::error_code& ec) const
  {
    return socket_ops::available(impl.socket_, ec);
  }

  boost::system::error_code listen(base_implementation_type& impl,
      int backlog, boost::system::error_code& ec)
  {
    socket_ops::listen(impl.socket_, backlog, ec);
    return ec;
  }

  template <typename IO_Control_Command>
  boost::system::error_code io_control(base_implementation_type& impl,
      IO_Control_Command& command, boost::system::error_code& ec)
  {
    socket_ops::ioctl(impl.socket_, impl.state_, command.name(),
        static_cast<ioctl_arg_type*>(command.data()), ec);
    return ec;
  }

  bool non_blocking(const base_implementation_type& impl) const
  {
    return (impl.state_ & socket_ops::user_set_non_blocking) != 0;
  }

  bool native_non_blocking(const base_implementation_type& impl) const
  {
    return (impl.state_ & socket_ops::internal_non_blocking) != 0;
  }

  boost::system::error_code shutdown(base_implementation_type& impl,
      socket_base::shutdown_type what, boost::system::error_code& ec)
  {
    socket_ops::shutdown(impl.socket_, what, ec);
    return ec;
  }

  template <typename ConstBufferSequence>
  size_t send(base_implementation_type& impl,
      const ConstBufferSequence& buffers,
      socket_base::message_flags flags, boost::system::error_code& ec)
  {
    buffer_sequence_adapter<boost::asio::const_buffer,
        ConstBufferSequence> bufs(buffers);

    return socket_ops::sync_send(impl.socket_, impl.state_,
        bufs.buffers(), bufs.count(), flags, bufs.all_empty(), ec);
  }

  template <typename ConstBufferSequence, typename Handler>
  void async_send(base_implementation_type& impl,
      const ConstBufferSequence& buffers,
      socket_base::message_flags flags, Handler handler)
  {
    bool is_continuation =
      boost_asio_handler_cont_helpers::is_continuation(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef reactive_socket_send_op<ConstBufferSequence, Handler> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      boost_asio_handler_alloc_helpers::allocate(
        sizeof(op), handler), 0 };
    p.p = new (p.v) op(impl.socket_, buffers, flags, handler);

    BOOST_ASIO_HANDLER_CREATION((p.p, "socket", &impl, "async_send"));

    start_op(impl, reactor::write_op, p.p, is_continuation, true,
        ((impl.state_ & socket_ops::stream_oriented)
          && buffer_sequence_adapter<boost::asio::const_buffer,
            ConstBufferSequence>::all_empty(buffers)));
    p.v = p.p = 0;
  }

  template <typename MutableBufferSequence>
  size_t receive(base_implementation_type& impl,
      const MutableBufferSequence& buffers,
      socket_base::message_flags flags, boost::system::error_code& ec)
  {
    buffer_sequence_adapter<boost::asio::mutable_buffer,
        MutableBufferSequence> bufs(buffers);

    return socket_ops::sync_recv(impl.socket_, impl.state_,
        bufs.buffers(), bufs.count(), flags, bufs.all_empty(), ec);
  }

  template <typename MutableBufferSequence, typename Handler>
  void async_receive(base_implementation_type& impl,
      const MutableBufferSequence& buffers,
      socket_base::message_flags flags, Handler handler)
  {
    bool is_continuation =
      boost_asio_handler_cont_helpers::is_continuation(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef reactive_socket_recv_op<MutableBufferSequence, Handler> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      boost_asio_handler_alloc_helpers::allocate(
        sizeof(op), handler), 0 };
    p.p = new (p.v) op(impl.socket_, impl.state_, buffers, flags, handler);

    BOOST_ASIO_HANDLER_CREATION((p.p, "socket", &impl, "async_receive"));

    start_op(impl,
        (flags & socket_base::message_out_of_band)
          ? reactor::except_op : reactor::read_op,
        p.p, is_continuation,
        (flags & socket_base::message_out_of_band) == 0,
        ((impl.state_ & socket_ops::stream_oriented)
          && buffer_sequence_adapter<boost::asio::mutable_buffer,
            MutableBufferSequence>::all_empty(buffers)));
    p.v = p.p = 0;
  }

  template <typename MutableBufferSequence>
  size_t receive_with_flags(base_implementation_type& impl,
      const MutableBufferSequence& buffers,
      socket_base::message_flags in_flags,
      socket_base::message_flags& out_flags, boost::system::error_code& ec)
  {
    buffer_sequence_adapter<boost::asio::mutable_buffer,
        MutableBufferSequence> bufs(buffers);

    return socket_ops::sync_recvmsg(impl.socket_, impl.state_,
        bufs.buffers(), bufs.count(), in_flags, out_flags, ec);
  }

  template <typename MutableBufferSequence, typename Handler>
  void async_receive_with_flags(base_implementation_type& impl,
      const MutableBufferSequence& buffers, socket_base::message_flags in_flags,
      socket_base::message_flags& out_flags, Handler handler)
  {
    bool is_continuation =
      boost_asio_handler_cont_helpers::is_continuation(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef reactive_socket_recvmsg_op<MutableBufferSequence, Handler> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      boost_asio_handler_alloc_helpers::allocate(
        sizeof(op), handler), 0 };
    p.p = new (p.v) op(impl.socket_, buffers, in_flags, out_flags, handler);

    BOOST_ASIO_HANDLER_CREATION((p.p, "socket",
          &impl, "async_receive_with_flags"));

    start_op(impl,
        (in_flags & socket_base::message_out_of_band)
          ? reactor::except_op : reactor::read_op,
        p.p, is_continuation,
        (in_flags & socket_base::message_out_of_band) == 0, false);
    p.v = p.p = 0;
  }

  descriptor_read_op_base(int descriptor,
      const MutableBufferSequence& buffers, func_type complete_func)
    : reactor_op(&descriptor_read_op_base::do_perform, complete_func),
      descriptor_(descriptor),
      buffers_(buffers)
  {
  }


  static bool do_perform(reactor_op* base)
  {
    descriptor_read_op_base* o(static_cast<descriptor_read_op_base*>(base));

    buffer_sequence_adapter<boost::asio::mutable_buffer,
        MutableBufferSequence> bufs(o->buffers_);

    return descriptor_ops::non_blocking_read(o->descriptor_,
        bufs.buffers(), bufs.count(), o->ec_, o->bytes_transferred_);
  }


  descriptor_read_op(int descriptor,
      const MutableBufferSequence& buffers, Handler& handler)
    : descriptor_read_op_base<MutableBufferSequence>(
        descriptor, buffers, &descriptor_read_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler))
  {
  }


  static void do_complete(io_service_impl* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    descriptor_read_op* o(static_cast<descriptor_read_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };

    BOOST_ASIO_HANDLER_COMPLETION((o));

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder2<Handler, boost::system::error_code, std::size_t>
      handler(o->handler_, o->ec_, o->bytes_transferred_);
    p.h = boost::asio::detail::addressof(handler.handler_);
    p.reset();

    // Make the upcall if required.
    if (owner)
    {
      fenced_block b(fenced_block::half);
      BOOST_ASIO_HANDLER_INVOCATION_BEGIN((handler.arg1_, handler.arg2_));
      boost_asio_handler_invoke_helpers::invoke(handler, handler.handler_);
      BOOST_ASIO_HANDLER_INVOCATION_END;
    }
  }


template <typename Handler>
inline void* allocate(std::size_t s, Handler& h)
{
#if !defined(BOOST_ASIO_HAS_HANDLER_HOOKS)
  return ::operator new(s);
#else
  using boost::asio::asio_handler_allocate;
  return asio_handler_allocate(s, boost::asio::detail::addressof(h));
#endif
}


template <typename Handler>
inline void deallocate(void* p, std::size_t s, Handler& h)
{
#if !defined(BOOST_ASIO_HAS_HANDLER_HOOKS)
  ::operator delete(p);
#else
  using boost::asio::asio_handler_deallocate;
  asio_handler_deallocate(p, s, boost::asio::detail::addressof(h));
#endif
}


  signal_handler(Handler& h)
    : signal_op(&signal_handler::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(h))
  {
  }


  static void do_complete(io_service_impl* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    signal_handler* h(static_cast<signal_handler*>(base));
    ptr p = { boost::asio::detail::addressof(h->handler_), h, h };

    BOOST_ASIO_HANDLER_COMPLETION((h));

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder2<Handler, boost::system::error_code, int>
      handler(h->handler_, h->ec_, h->signal_number_);
    p.h = boost::asio::detail::addressof(handler.handler_);
    p.reset();

    // Make the upcall if required.
    if (owner)
    {
      fenced_block b(fenced_block::half);
      BOOST_ASIO_HANDLER_INVOCATION_BEGIN((handler.arg1_, handler.arg2_));
      boost_asio_handler_invoke_helpers::invoke(handler, handler.handler_);
      BOOST_ASIO_HANDLER_INVOCATION_END;
    }
  }

  boolean()
    : value_(0)
  {
  }

  explicit boolean(bool v)
    : value_(v ? 1 : 0)
  {
  }

  boolean& operator=(bool v)
  {
    value_ = v ? 1 : 0;
    return *this;
  }

  bool value() const
  {
    return !!value_;
  }

  operator bool() const
  {
    return !!value_;
  }

  bool operator!() const
  {
    return !value_;
  }

  template <typename Protocol>
  int level(const Protocol&) const
  {
    return Level;
  }

  template <typename Protocol>
  int name(const Protocol&) const
  {
    return Name;
  }

  template <typename Protocol>
  int* data(const Protocol&)
  {
    return &value_;
  }

  template <typename Protocol>
  const int* data(const Protocol&) const
  {
    return &value_;
  }

  template <typename Protocol>
  std::size_t size(const Protocol&) const
  {
    return sizeof(value_);
  }

  template <typename Protocol>
  void resize(const Protocol&, std::size_t s)
  {
    // On some platforms (e.g. Windows Vista), the getsockopt function will
    // return the size of a boolean socket option as one byte, even though a
    // four byte integer was passed in.
    switch (s)
    {
    case sizeof(char):
      value_ = *reinterpret_cast<char*>(&value_) ? 1 : 0;
      break;
    case sizeof(value_):
      break;
    default:
      {
        std::length_error ex("boolean socket option resize");
        boost::asio::detail::throw_exception(ex);
      }
    }
  }

  integer()
    : value_(0)
  {
  }

  explicit integer(int v)
    : value_(v)
  {
  }

  integer& operator=(int v)
  {
    value_ = v;
    return *this;
  }

  int value() const
  {
    return value_;
  }

  template <typename Protocol>
  int level(const Protocol&) const
  {
    return Level;
  }

  template <typename Protocol>
  int name(const Protocol&) const
  {
    return Name;
  }

  template <typename Protocol>
  int* data(const Protocol&)
  {
    return &value_;
  }

  template <typename Protocol>
  const int* data(const Protocol&) const
  {
    return &value_;
  }

  template <typename Protocol>
  std::size_t size(const Protocol&) const
  {
    return sizeof(value_);
  }

  template <typename Protocol>
  void resize(const Protocol&, std::size_t s)
  {
    if (s != sizeof(value_))
    {
      std::length_error ex("integer socket option resize");
      boost::asio::detail::throw_exception(ex);
    }
  }

  linger()
  {
    value_.l_onoff = 0;
    value_.l_linger = 0;
  }

  linger(bool e, int t)
  {
    enabled(e);
    timeout BOOST_ASIO_PREVENT_MACRO_SUBSTITUTION(t);
  }

  void enabled(bool value)
  {
    value_.l_onoff = value ? 1 : 0;
  }

  bool enabled() const
  {
    return value_.l_onoff != 0;
  }

  buffer_resize_guard(Buffer& buffer)
    : buffer_(buffer),
      old_size_(buffer.size())
  {
  }

  ~buffer_resize_guard()
  {
    if (old_size_ != (std::numeric_limits<size_t>::max)())
    {
      buffer_.resize(old_size_);
    }
  }

  void commit()
  {
    old_size_ = (std::numeric_limits<size_t>::max)();
  }

  binder1(const Handler& handler, const Arg1& arg1)
    : handler_(handler),
      arg1_(arg1)
  {
  }


  binder1(Handler& handler, const Arg1& arg1)
    : handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      arg1_(arg1)
  {
  }


  void operator()()
  {
    handler_(static_cast<const Arg1&>(arg1_));
  }


  void operator()() const
  {
    handler_(arg1_);
  }


template <typename Handler, typename Arg1>
inline void* asio_handler_allocate(std::size_t size,
    binder1<Handler, Arg1>* this_handler)
{
  return boost_asio_handler_alloc_helpers::allocate(
      size, this_handler->handler_);
}


template <typename Handler, typename Arg1>
inline void asio_handler_deallocate(void* pointer, std::size_t size,
    binder1<Handler, Arg1>* this_handler)
{
  boost_asio_handler_alloc_helpers::deallocate(
      pointer, size, this_handler->handler_);
}


template <typename Handler, typename Arg1>
inline bool asio_handler_is_continuation(
    binder1<Handler, Arg1>* this_handler)
{
  return boost_asio_handler_cont_helpers::is_continuation(
      this_handler->handler_);
}


template <typename Function, typename Handler, typename Arg1>
inline void asio_handler_invoke(Function& function,
    binder1<Handler, Arg1>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
}


template <typename Function, typename Handler, typename Arg1>
inline void asio_handler_invoke(const Function& function,
    binder1<Handler, Arg1>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
}


template <typename Handler, typename Arg1>
inline binder1<Handler, Arg1> bind_handler(Handler handler,
    const Arg1& arg1)
{
  return binder1<Handler, Arg1>(handler, arg1);
}

  binder2(const Handler& handler, const Arg1& arg1, const Arg2& arg2)
    : handler_(handler),
      arg1_(arg1),
      arg2_(arg2)
  {
  }


  binder2(Handler& handler, const Arg1& arg1, const Arg2& arg2)
    : handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      arg1_(arg1),
      arg2_(arg2)
  {
  }


  void operator()()
  {
    handler_(static_cast<const Arg1&>(arg1_),
        static_cast<const Arg2&>(arg2_));
  }


  void operator()() const
  {
    handler_(arg1_, arg2_);
  }


template <typename Handler, typename Arg1, typename Arg2>
inline bool asio_handler_is_continuation(
    binder2<Handler, Arg1, Arg2>* this_handler)
{
  return boost_asio_handler_cont_helpers::is_continuation(
      this_handler->handler_);
}


template <typename Function, typename Handler, typename Arg1, typename Arg2>
inline void asio_handler_invoke(Function& function,
    binder2<Handler, Arg1, Arg2>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
}


template <typename Function, typename Handler, typename Arg1, typename Arg2>
inline void asio_handler_invoke(const Function& function,
    binder2<Handler, Arg1, Arg2>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
}


template <typename Handler, typename Arg1, typename Arg2>
inline binder2<Handler, Arg1, Arg2> bind_handler(Handler handler,
    const Arg1& arg1, const Arg2& arg2)
{
  return binder2<Handler, Arg1, Arg2>(handler, arg1, arg2);
}

  binder3(const Handler& handler, const Arg1& arg1, const Arg2& arg2,
      const Arg3& arg3)
    : handler_(handler),
      arg1_(arg1),
      arg2_(arg2),
      arg3_(arg3)
  {
  }


  binder3(Handler& handler, const Arg1& arg1, const Arg2& arg2,
      const Arg3& arg3)
    : handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      arg1_(arg1),
      arg2_(arg2),
      arg3_(arg3)
  {
  }


  void operator()()
  {
    handler_(static_cast<const Arg1&>(arg1_),
        static_cast<const Arg2&>(arg2_),
        static_cast<const Arg3&>(arg3_));
  }


  void operator()() const
  {
    handler_(arg1_, arg2_, arg3_);
  }


template <typename Handler, typename Arg1, typename Arg2, typename Arg3>
inline bool asio_handler_is_continuation(
    binder3<Handler, Arg1, Arg2, Arg3>* this_handler)
{
  return boost_asio_handler_cont_helpers::is_continuation(
      this_handler->handler_);
}


template <typename Function, typename Handler, typename Arg1, typename Arg2,
    typename Arg3>
inline void asio_handler_invoke(Function& function,
    binder3<Handler, Arg1, Arg2, Arg3>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
}


template <typename Function, typename Handler, typename Arg1, typename Arg2,
    typename Arg3>
inline void asio_handler_invoke(const Function& function,
    binder3<Handler, Arg1, Arg2, Arg3>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
}


template <typename Handler, typename Arg1, typename Arg2, typename Arg3>
inline binder3<Handler, Arg1, Arg2, Arg3> bind_handler(Handler handler,
    const Arg1& arg1, const Arg2& arg2, const Arg3& arg3)
{
  return binder3<Handler, Arg1, Arg2, Arg3>(handler, arg1, arg2, arg3);
}

  binder4(const Handler& handler, const Arg1& arg1, const Arg2& arg2,
      const Arg3& arg3, const Arg4& arg4)
    : handler_(handler),
      arg1_(arg1),
      arg2_(arg2),
      arg3_(arg3),
      arg4_(arg4)
  {
  }


  binder4(Handler& handler, const Arg1& arg1, const Arg2& arg2,
      const Arg3& arg3, const Arg4& arg4)
    : handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      arg1_(arg1),
      arg2_(arg2),
      arg3_(arg3),
      arg4_(arg4)
  {
  }


  void operator()()
  {
    handler_(static_cast<const Arg1&>(arg1_),
        static_cast<const Arg2&>(arg2_),
        static_cast<const Arg3&>(arg3_),
        static_cast<const Arg4&>(arg4_));
  }


  void operator()() const
  {
    handler_(arg1_, arg2_, arg3_, arg4_);
  }


template <typename Handler, typename Arg1, typename Arg2, typename Arg3,
    typename Arg4>
inline bool asio_handler_is_continuation(
    binder4<Handler, Arg1, Arg2, Arg3, Arg4>* this_handler)
{
  return boost_asio_handler_cont_helpers::is_continuation(
      this_handler->handler_);
}


template <typename Function, typename Handler, typename Arg1, typename Arg2,
    typename Arg3, typename Arg4>
inline void asio_handler_invoke(Function& function,
    binder4<Handler, Arg1, Arg2, Arg3, Arg4>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
}


template <typename Function, typename Handler, typename Arg1, typename Arg2,
    typename Arg3, typename Arg4>
inline void asio_handler_invoke(const Function& function,
    binder4<Handler, Arg1, Arg2, Arg3, Arg4>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
}


template <typename Handler, typename Arg1, typename Arg2, typename Arg3,
    typename Arg4>
inline binder4<Handler, Arg1, Arg2, Arg3, Arg4> bind_handler(
    Handler handler, const Arg1& arg1, const Arg2& arg2,
    const Arg3& arg3, const Arg4& arg4)
{
  return binder4<Handler, Arg1, Arg2, Arg3, Arg4>(handler, arg1, arg2, arg3,
      arg4);
}

  binder5(const Handler& handler, const Arg1& arg1, const Arg2& arg2,
      const Arg3& arg3, const Arg4& arg4, const Arg5& arg5)
    : handler_(handler),
      arg1_(arg1),
      arg2_(arg2),
      arg3_(arg3),
      arg4_(arg4),
      arg5_(arg5)
  {
  }


  binder5(Handler& handler, const Arg1& arg1, const Arg2& arg2,
      const Arg3& arg3, const Arg4& arg4, const Arg5& arg5)
    : handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      arg1_(arg1),
      arg2_(arg2),
      arg3_(arg3),
      arg4_(arg4),
      arg5_(arg5)
  {
  }


  void operator()()
  {
    handler_(static_cast<const Arg1&>(arg1_),
        static_cast<const Arg2&>(arg2_),
        static_cast<const Arg3&>(arg3_),
        static_cast<const Arg4&>(arg4_),
        static_cast<const Arg5&>(arg5_));
  }


  void operator()() const
  {
    handler_(arg1_, arg2_, arg3_, arg4_, arg5_);
  }


template <typename Handler, typename Arg1, typename Arg2, typename Arg3,
    typename Arg4, typename Arg5>
inline bool asio_handler_is_continuation(
    binder5<Handler, Arg1, Arg2, Arg3, Arg4, Arg5>* this_handler)
{
  return boost_asio_handler_cont_helpers::is_continuation(
      this_handler->handler_);
}


template <typename Function, typename Handler, typename Arg1, typename Arg2,
    typename Arg3, typename Arg4, typename Arg5>
inline void asio_handler_invoke(Function& function,
    binder5<Handler, Arg1, Arg2, Arg3, Arg4, Arg5>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
}


template <typename Function, typename Handler, typename Arg1, typename Arg2,
    typename Arg3, typename Arg4, typename Arg5>
inline void asio_handler_invoke(const Function& function,
    binder5<Handler, Arg1, Arg2, Arg3, Arg4, Arg5>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
}


template <typename Handler, typename Arg1, typename Arg2, typename Arg3,
    typename Arg4, typename Arg5>
inline binder5<Handler, Arg1, Arg2, Arg3, Arg4, Arg5> bind_handler(
    Handler handler, const Arg1& arg1, const Arg2& arg2,
    const Arg3& arg3, const Arg4& arg4, const Arg5& arg5)
{
  return binder5<Handler, Arg1, Arg2, Arg3, Arg4, Arg5>(handler, arg1, arg2,
      arg3, arg4, arg5);
}

  void init()
  {
  }

  void lock()
  {
  }

  void unlock()
  {
  }

  socket_holder()
    : socket_(invalid_socket)
  {
  }

  ~socket_holder()
  {
    if (socket_ != invalid_socket)
    {
      boost::system::error_code ec;
      socket_ops::state_type state = 0;
      socket_ops::close(socket_, state, true, ec);
    }
  }

  socket_type get() const
  {
    return socket_;
  }

  void reset()
  {
    if (socket_ != invalid_socket)
    {
      boost::system::error_code ec;
      socket_ops::state_type state = 0;
      socket_ops::close(socket_, state, true, ec);
      socket_ = invalid_socket;
    }
  }

  socket_type release()
  {
    socket_type tmp = socket_;
    socket_ = invalid_socket;
    return tmp;
  }

  null_event()
  {
  }

  ~null_event()
  {
  }

  template <typename Lock>
  void signal(Lock&)
  {
  }

  template <typename Lock>
  void signal_and_unlock(Lock&)
  {
  }

  template <typename Lock>
  void clear(Lock&)
  {
  }

  template <typename Lock>
  void wait(Lock&)
  {
  }

    ~auto_service_ptr() { destroy(ptr_); }

    explicit context(Key* k)
      : key_(k),
        next_(call_stack<Key, Value>::top_)
    {
      value_ = reinterpret_cast<unsigned char*>(this);
      call_stack<Key, Value>::top_ = this;
    }

    context(Key* k, Value& v)
      : key_(k),
        value_(&v),
        next_(call_stack<Key, Value>::top_)
    {
      call_stack<Key, Value>::top_ = this;
    }

    ~context()
    {
      call_stack<Key, Value>::top_ = next_;
    }

    Value* next_by_key() const
    {
      context* elem = next_;
      while (elem)
      {
        if (elem->key_ == key_)
          return elem->value_;
        elem = elem->next_;
      }
      return 0;
    }

  static Value* contains(Key* k)
  {
    context* elem = top_;
    while (elem)
    {
      if (elem->key_ == k)
        return elem->value_;
      elem = elem->next_;
    }
    return 0;
  }

  static Value* top()
  {
    context* elem = top_;
    return elem ? elem->value_ : 0;
  }


template <typename ReturnType>
inline ReturnType error_wrapper(ReturnType return_value,
    boost::system::error_code& ec)
{
  ec = boost::system::error_code(errno,
      boost::asio::error::get_system_category());
  return return_value;
}

  explicit gcc_x86_fenced_block(half_t)
  {
  }

  explicit gcc_x86_fenced_block(full_t)
  {
    lbarrier();
  }

  ~gcc_x86_fenced_block()
  {
    sbarrier();
  }

  static int barrier()
  {
    int r = 0, m = 1;
    __asm__ __volatile__ (
        "xchgl %0, %1" :
        "=r"(r), "=m"(m) :
        "0"(1), "m"(m) :
        "memory", "cc");
    return r;
  }


  static void lbarrier()
  {
#if defined(__SSE2__)
    __asm__ __volatile__ ("lfence" ::: "memory");
#else // defined(__SSE2__)
    barrier();
#endif // defined(__SSE2__)
  }


  static void sbarrier()
  {
#if defined(__SSE2__)
    __asm__ __volatile__ ("sfence" ::: "memory");
#else // defined(__SSE2__)
    barrier();
#endif // defined(__SSE2__)
  }


template <typename Context>
inline bool is_continuation(Context& context)
{
#if !defined(BOOST_ASIO_HAS_HANDLER_HOOKS)
  return false;
#else
  using boost::asio::asio_handler_is_continuation;
  return asio_handler_is_continuation(
      boost::asio::detail::addressof(context));
#endif
}

  int read_descriptor() const
  {
    return read_descriptor_;
  }


inline void throw_error(const boost::system::error_code& err)
{
  if (err)
    do_throw_error(err);
}


template <typename Function, typename Context>
inline void invoke(Function& function, Context& context)
{
#if !defined(BOOST_ASIO_HAS_HANDLER_HOOKS)
  Function tmp(function);
  tmp();
#else
  using boost::asio::asio_handler_invoke;
  asio_handler_invoke(function, boost::asio::detail::addressof(context));
#endif
}


template <typename Function, typename Context>
inline void invoke(const Function& function, Context& context)
{
#if !defined(BOOST_ASIO_HAS_HANDLER_HOOKS)
  Function tmp(function);
  tmp();
#else
  using boost::asio::asio_handler_invoke;
  asio_handler_invoke(function, boost::asio::detail::addressof(context));
#endif
}

  explicit null_fenced_block(half_or_full_t)
  {
  }

  ~null_fenced_block()
  {
  }

  null_mutex()
  {
  }

  ~null_mutex()
  {
  }

  void lock()
  {
  }

  void unlock()
  {
  }

  reactive_socket_send_op_base(socket_type socket,
      const ConstBufferSequence& buffers,
      socket_base::message_flags flags, func_type complete_func)
    : reactor_op(&reactive_socket_send_op_base::do_perform, complete_func),
      socket_(socket),
      buffers_(buffers),
      flags_(flags)
  {
  }


  static bool do_perform(reactor_op* base)
  {
    reactive_socket_send_op_base* o(
        static_cast<reactive_socket_send_op_base*>(base));

    buffer_sequence_adapter<boost::asio::const_buffer,
        ConstBufferSequence> bufs(o->buffers_);

    return socket_ops::non_blocking_send(o->socket_,
          bufs.buffers(), bufs.count(), o->flags_,
          o->ec_, o->bytes_transferred_);
  }


  reactive_socket_send_op(socket_type socket,
      const ConstBufferSequence& buffers,
      socket_base::message_flags flags, Handler& handler)
    : reactive_socket_send_op_base<ConstBufferSequence>(socket,
        buffers, flags, &reactive_socket_send_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler))
  {
  }


  static void do_complete(io_service_impl* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    reactive_socket_send_op* o(static_cast<reactive_socket_send_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };

    BOOST_ASIO_HANDLER_COMPLETION((o));

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder2<Handler, boost::system::error_code, std::size_t>
      handler(o->handler_, o->ec_, o->bytes_transferred_);
    p.h = boost::asio::detail::addressof(handler.handler_);
    p.reset();

    // Make the upcall if required.
    if (owner)
    {
      fenced_block b(fenced_block::half);
      BOOST_ASIO_HANDLER_INVOCATION_BEGIN((handler.arg1_, handler.arg2_));
      boost_asio_handler_invoke_helpers::invoke(handler, handler.handler_);
      BOOST_ASIO_HANDLER_INVOCATION_END;
    }
  }

  non_blocking_io()
    : value_(0)
  {
  }

  non_blocking_io(bool value)
    : value_(value ? 1 : 0)
  {
  }

  int name() const
  {
    return static_cast<int>(FIONBIO);
  }

  void set(bool value)
  {
    value_ = value ? 1 : 0;
  }

  bool get() const
  {
    return value_ != 0;
  }

  detail::ioctl_arg_type* data()
  {
    return &value_;
  }

  bytes_readable()
    : value_(0)
  {
  }

  int name() const
  {
    return static_cast<int>(FIONREAD);
  }

  void set(std::size_t value)
  {
    value_ = static_cast<detail::ioctl_arg_type>(value);
  }

  std::size_t get() const
  {
    return static_cast<std::size_t>(value_);
  }

  detail::ioctl_arg_type* data()
  {
    return &value_;
  }

    implementation_type()
      : descriptor_(-1),
        state_(0)
    {
    }

  bool is_open(const implementation_type& impl) const
  {
    return impl.descriptor_ != -1;
  }

  native_handle_type native_handle(const implementation_type& impl) const
  {
    return impl.descriptor_;
  }

  template <typename IO_Control_Command>
  boost::system::error_code io_control(implementation_type& impl,
      IO_Control_Command& command, boost::system::error_code& ec)
  {
    descriptor_ops::ioctl(impl.descriptor_, impl.state_,
        command.name(), static_cast<ioctl_arg_type*>(command.data()), ec);
    return ec;
  }

  bool non_blocking(const implementation_type& impl) const
  {
    return (impl.state_ & descriptor_ops::user_set_non_blocking) != 0;
  }

  bool native_non_blocking(const implementation_type& impl) const
  {
    return (impl.state_ & descriptor_ops::internal_non_blocking) != 0;
  }

  template <typename ConstBufferSequence>
  size_t write_some(implementation_type& impl,
      const ConstBufferSequence& buffers, boost::system::error_code& ec)
  {
    buffer_sequence_adapter<boost::asio::const_buffer,
        ConstBufferSequence> bufs(buffers);

    return descriptor_ops::sync_write(impl.descriptor_, impl.state_,
        bufs.buffers(), bufs.count(), bufs.all_empty(), ec);
  }

  template <typename ConstBufferSequence, typename Handler>
  void async_write_some(implementation_type& impl,
      const ConstBufferSequence& buffers, Handler& handler)
  {
    bool is_continuation =
      boost_asio_handler_cont_helpers::is_continuation(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef descriptor_write_op<ConstBufferSequence, Handler> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      boost_asio_handler_alloc_helpers::allocate(
        sizeof(op), handler), 0 };
    p.p = new (p.v) op(impl.descriptor_, buffers, handler);

    BOOST_ASIO_HANDLER_CREATION((p.p, "descriptor", &impl, "async_write_some"));

    start_op(impl, reactor::write_op, p.p, is_continuation, true,
        buffer_sequence_adapter<boost::asio::const_buffer,
          ConstBufferSequence>::all_empty(buffers));
    p.v = p.p = 0;
  }

  template <typename MutableBufferSequence>
  size_t read_some(implementation_type& impl,
      const MutableBufferSequence& buffers, boost::system::error_code& ec)
  {
    buffer_sequence_adapter<boost::asio::mutable_buffer,
        MutableBufferSequence> bufs(buffers);

    return descriptor_ops::sync_read(impl.descriptor_, impl.state_,
        bufs.buffers(), bufs.count(), bufs.all_empty(), ec);
  }

  template <typename MutableBufferSequence, typename Handler>
  void async_read_some(implementation_type& impl,
      const MutableBufferSequence& buffers, Handler& handler)
  {
    bool is_continuation =
      boost_asio_handler_cont_helpers::is_continuation(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef descriptor_read_op<MutableBufferSequence, Handler> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      boost_asio_handler_alloc_helpers::allocate(
        sizeof(op), handler), 0 };
    p.p = new (p.v) op(impl.descriptor_, buffers, handler);

    BOOST_ASIO_HANDLER_CREATION((p.p, "descriptor", &impl, "async_read_some"));

    start_op(impl, reactor::read_op, p.p, is_continuation, true,
        buffer_sequence_adapter<boost::asio::mutable_buffer,
          MutableBufferSequence>::all_empty(buffers));
    p.v = p.p = 0;
  }


  static void init_iov_base(void*& base, void* addr)
  {
    base = addr;
  }


  template <typename T>
  static void init_iov_base(T& base, void* addr)
  {
    base = static_cast<T>(addr);
  }


  static void init_native_buffer(iovec& iov,
      const boost::asio::mutable_buffer& buffer)
  {
    init_iov_base(iov.iov_base, boost::asio::buffer_cast<void*>(buffer));
    iov.iov_len = boost::asio::buffer_size(buffer);
  }

  explicit buffer_sequence_adapter(const Buffers& buffer_sequence)
    : count_(0), total_buffer_size_(0)
  {
    typename Buffers::const_iterator iter = buffer_sequence.begin();
    typename Buffers::const_iterator end = buffer_sequence.end();
    for (; iter != end && count_ < max_buffers; ++iter, ++count_)
    {
      Buffer buffer(*iter);
      init_native_buffer(buffers_[count_], buffer);
      total_buffer_size_ += boost::asio::buffer_size(buffer);
    }
  }


  native_buffer_type* buffers()
  {
    return buffers_;
  }


  std::size_t count() const
  {
    return count_;
  }


  bool all_empty() const
  {
    return total_buffer_size_ == 0;
  }


  static bool all_empty(const Buffers& buffer_sequence)
  {
    typename Buffers::const_iterator iter = buffer_sequence.begin();
    typename Buffers::const_iterator end = buffer_sequence.end();
    std::size_t i = 0;
    for (; iter != end && i < max_buffers; ++iter, ++i)
      if (boost::asio::buffer_size(Buffer(*iter)) > 0)
        return false;
    return true;
  }


  static void validate(const Buffers& buffer_sequence)
  {
    typename Buffers::const_iterator iter = buffer_sequence.begin();
    typename Buffers::const_iterator end = buffer_sequence.end();
    for (; iter != end; ++iter)
    {
      Buffer buffer(*iter);
      boost::asio::buffer_cast<const void*>(buffer);
    }
  }


  static Buffer first(const Buffers& buffer_sequence)
  {
    typename Buffers::const_iterator iter = buffer_sequence.begin();
    typename Buffers::const_iterator end = buffer_sequence.end();
    for (; iter != end; ++iter)
    {
      Buffer buffer(*iter);
      if (boost::asio::buffer_size(buffer) != 0)
        return buffer;
    }
    return Buffer();
  }

  bool perform()
  {
    return perform_func_(this);
  }


  reactor_op(perform_func_type perform_func, func_type complete_func)
    : operation(complete_func),
      bytes_transferred_(0),
      perform_func_(perform_func)
  {
  }


  reactive_null_buffers_op(Handler& handler)
    : reactor_op(&reactive_null_buffers_op::do_perform,
        &reactive_null_buffers_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler))
  {
  }


  static bool do_perform(reactor_op*)
  {
    return true;
  }


  static void do_complete(io_service_impl* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    reactive_null_buffers_op* o(static_cast<reactive_null_buffers_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };

    BOOST_ASIO_HANDLER_COMPLETION((o));

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder2<Handler, boost::system::error_code, std::size_t>
      handler(o->handler_, o->ec_, o->bytes_transferred_);
    p.h = boost::asio::detail::addressof(handler.handler_);
    p.reset();

    // Make the upcall if required.
    if (owner)
    {
      fenced_block b(fenced_block::half);
      BOOST_ASIO_HANDLER_INVOCATION_BEGIN((handler.arg1_, handler.arg2_));
      boost_asio_handler_invoke_helpers::invoke(handler, handler.handler_);
      BOOST_ASIO_HANDLER_INVOCATION_END;
    }
  }

  descriptor_write_op_base(int descriptor,
      const ConstBufferSequence& buffers, func_type complete_func)
    : reactor_op(&descriptor_write_op_base::do_perform, complete_func),
      descriptor_(descriptor),
      buffers_(buffers)
  {
  }


  static bool do_perform(reactor_op* base)
  {
    descriptor_write_op_base* o(static_cast<descriptor_write_op_base*>(base));

    buffer_sequence_adapter<boost::asio::const_buffer,
        ConstBufferSequence> bufs(o->buffers_);

    return descriptor_ops::non_blocking_write(o->descriptor_,
        bufs.buffers(), bufs.count(), o->ec_, o->bytes_transferred_);
  }


  descriptor_write_op(int descriptor,
      const ConstBufferSequence& buffers, Handler& handler)
    : descriptor_write_op_base<ConstBufferSequence>(
        descriptor, buffers, &descriptor_write_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler))
  {
  }


  static void do_complete(io_service_impl* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    descriptor_write_op* o(static_cast<descriptor_write_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };

    BOOST_ASIO_HANDLER_COMPLETION((o));

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder2<Handler, boost::system::error_code, std::size_t>
      handler(o->handler_, o->ec_, o->bytes_transferred_);
    p.h = boost::asio::detail::addressof(handler.handler_);
    p.reset();

    // Make the upcall if required.
    if (owner)
    {
      fenced_block b(fenced_block::half);
      BOOST_ASIO_HANDLER_INVOCATION_BEGIN((handler.arg1_, handler.arg2_));
      boost_asio_handler_invoke_helpers::invoke(handler, handler.handler_);
      BOOST_ASIO_HANDLER_INVOCATION_END;
    }
  }

  noncopyable() {}

  ~noncopyable() {}


  resolve_endpoint_op(socket_ops::weak_cancel_token_type cancel_token,
      const endpoint_type& endpoint, io_service_impl& ios, Handler& handler)
    : operation(&resolve_endpoint_op::do_complete),
      cancel_token_(cancel_token),
      endpoint_(endpoint),
      io_service_impl_(ios),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler))
  {
  }


  static void do_complete(io_service_impl* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the operation object.
    resolve_endpoint_op* o(static_cast<resolve_endpoint_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };

    if (owner && owner != &o->io_service_impl_)
    {
      // The operation is being run on the worker io_service. Time to perform
      // the resolver operation.
    
      // Perform the blocking endpoint resolution operation.
      char host_name[NI_MAXHOST];
      char service_name[NI_MAXSERV];
      socket_ops::background_getnameinfo(o->cancel_token_, o->endpoint_.data(),
          o->endpoint_.size(), host_name, NI_MAXHOST, service_name, NI_MAXSERV,
          o->endpoint_.protocol().type(), o->ec_);
      o->iter_ = iterator_type::create(o->endpoint_, host_name, service_name);

      // Pass operation back to main io_service for completion.
      o->io_service_impl_.post_deferred_completion(o);
      p.v = p.p = 0;
    }
    else
    {
      // The operation has been returned to the main io_service. The completion
      // handler is ready to be delivered.

      BOOST_ASIO_HANDLER_COMPLETION((o));

      // Make a copy of the handler so that the memory can be deallocated
      // before the upcall is made. Even if we're not about to make an upcall,
      // a sub-object of the handler may be the true owner of the memory
      // associated with the handler. Consequently, a local copy of the handler
      // is required to ensure that any owning sub-object remains valid until
      // after we have deallocated the memory here.
      detail::binder2<Handler, boost::system::error_code, iterator_type>
        handler(o->handler_, o->ec_, o->iter_);
      p.h = boost::asio::detail::addressof(handler.handler_);
      p.reset();

      if (owner)
      {
        fenced_block b(fenced_block::half);
        BOOST_ASIO_HANDLER_INVOCATION_BEGIN((handler.arg1_, "..."));
        boost_asio_handler_invoke_helpers::invoke(handler, handler.handler_);
        BOOST_ASIO_HANDLER_INVOCATION_END;
      }
    }
  }

  static time_type now()
  {
    return clock_type::now();
  }

  static time_type add(const time_type& t, const duration_type& d)
  {
    const time_type epoch;
    if (t >= epoch)
    {
      if ((time_type::max)() - t < d)
        return (time_type::max)();
    }
    else // t < epoch
    {
      if (-(t - (time_type::min)()) > d)
        return (time_type::min)();
    }

    return t + d;
  }

  static duration_type subtract(const time_type& t1, const time_type& t2)
  {
    const time_type epoch;
    if (t1 >= epoch)
    {
      if (t2 >= epoch)
      {
        return t1 - t2;
      }
      else if (t2 == (time_type::min)())
      {
        return (duration_type::max)();
      }
      else if ((time_type::max)() - t1 < epoch - t2)
      {
        return (duration_type::max)();
      }
      else
      {
        return t1 - t2;
      }
    }
    else // t1 < epoch
    {
      if (t2 < epoch)
      {
        return t1 - t2;
      }
      else if (t1 == (time_type::min)())
      {
        return (duration_type::min)();
      }
      else if ((time_type::max)() - t2 < epoch - t1)
      {
        return (duration_type::min)();
      }
      else
      {
        return -(t2 - t1);
      }
    }
  }

  static bool less_than(const time_type& t1, const time_type& t2)
  {
    return t1 < t2;
  }

    explicit posix_time_duration(const duration_type& d)
      : d_(d)
    {
    }


    int64_t ticks() const
    {
      return d_.count();
    }


    int64_t total_seconds() const
    {
      return duration_cast<1, 1>();
    }


    int64_t total_milliseconds() const
    {
      return duration_cast<1, 1000>();
    }


    int64_t total_microseconds() const
    {
      return duration_cast<1, 1000000>();
    }

    template <int64_t Num, int64_t Den>
    int64_t duration_cast() const
    {
      const int64_t num = period_type::num * Den;
      const int64_t den = period_type::den * Num;

      if (num == 1 && den == 1)
        return ticks();
      else if (num != 1 && den == 1)
        return ticks() * num;
      else if (num == 1 && period_type::den != 1)
        return ticks() / den;
      else
        return ticks() * num / den;
    }

  static posix_time_duration to_posix_duration(const duration_type& d)
  {
    return posix_time_duration(WaitTraits::to_wait_duration(d));
  }

  void work_started()
  {
    ++outstanding_work_;
  }

  void work_finished()
  {
    if (--outstanding_work_ == 0)
      stop();
  }

  bool can_dispatch()
  {
    return thread_call_stack::contains(this) != 0;
  }

    task_operation() : operation(0) {}

    task_operation() : operation(0) {}

  resolver_service(boost::asio::io_service& io_service)
    : resolver_service_base(io_service)
  {
  }

  iterator_type resolve(implementation_type&, const query_type& query,
      boost::system::error_code& ec)
  {
    boost::asio::detail::addrinfo_type* address_info = 0;

    socket_ops::getaddrinfo(query.host_name().c_str(),
        query.service_name().c_str(), query.hints(), &address_info, ec);
    auto_addrinfo auto_address_info(address_info);

    return ec ? iterator_type() : iterator_type::create(
        address_info, query.host_name(), query.service_name());
  }

  template <typename Handler>
  void async_resolve(implementation_type& impl,
      const query_type& query, Handler& handler)
  {
    // Allocate and construct an operation to wrap the handler.
    typedef resolve_op<Protocol, Handler> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      boost_asio_handler_alloc_helpers::allocate(
        sizeof(op), handler), 0 };
    p.p = new (p.v) op(impl, query, io_service_impl_, handler);

    BOOST_ASIO_HANDLER_CREATION((p.p, "resolver", &impl, "async_resolve"));

    start_resolve_op(p.p);
    p.v = p.p = 0;
  }

  template <typename Handler>
  void async_resolve(implementation_type& impl,
      const endpoint_type& endpoint, Handler& handler)
  {
    // Allocate and construct an operation to wrap the handler.
    typedef resolve_endpoint_op<Protocol, Handler> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      boost_asio_handler_alloc_helpers::allocate(
        sizeof(op), handler), 0 };
    p.p = new (p.v) op(impl, endpoint, io_service_impl_, handler);

    BOOST_ASIO_HANDLER_CREATION((p.p, "resolver", &impl, "async_resolve"));

    start_resolve_op(p.p);
    p.v = p.p = 0;
  }

  template <typename Operation>
  static Operation* next(Operation* o)
  {
    return static_cast<Operation*>(o->next_);
  }


  template <typename Operation1, typename Operation2>
  static void next(Operation1*& o1, Operation2* o2)
  {
    o1->next_ = o2;
  }


  template <typename Operation>
  static void destroy(Operation* o)
  {
    o->destroy();
  }


  template <typename Operation>
  static Operation*& front(op_queue<Operation>& q)
  {
    return q.front_;
  }


  template <typename Operation>
  static Operation*& back(op_queue<Operation>& q)
  {
    return q.back_;
  }

  op_queue()
    : front_(0),
      back_(0)
  {
  }

  ~op_queue()
  {
    while (Operation* op = front_)
    {
      pop();
      op_queue_access::destroy(op);
    }
  }

  Operation* front()
  {
    return front_;
  }

  void pop()
  {
    if (front_)
    {
      Operation* tmp = front_;
      front_ = op_queue_access::next(front_);
      if (front_ == 0)
        back_ = 0;
      op_queue_access::next(tmp, static_cast<Operation*>(0));
    }
  }

  void push(Operation* h)
  {
    op_queue_access::next(h, static_cast<Operation*>(0));
    if (back_)
    {
      op_queue_access::next(back_, h);
      back_ = h;
    }
    else
    {
      front_ = back_ = h;
    }
  }

  template <typename OtherOperation>
  void push(op_queue<OtherOperation>& q)
  {
    if (Operation* other_front = op_queue_access::front(q))
    {
      if (back_)
        op_queue_access::next(back_, other_front);
      else
        front_ = other_front;
      back_ = op_queue_access::back(q);
      op_queue_access::front(q) = 0;
      op_queue_access::back(q) = 0;
    }
  }

  bool empty() const
  {
    return front_ == 0;
  }

  thread_info_base()
    : reusable_memory_(0)
  {
  }


  ~thread_info_base()
  {
    if (reusable_memory_)
      ::operator delete(reusable_memory_);
  }


  static void* allocate(thread_info_base* this_thread, std::size_t size)
  {
    if (this_thread && this_thread->reusable_memory_)
    {
      void* const pointer = this_thread->reusable_memory_;
      this_thread->reusable_memory_ = 0;

      unsigned char* const mem = static_cast<unsigned char*>(pointer);
      if (static_cast<std::size_t>(mem[0]) >= size)
      {
        mem[size] = mem[0];
        return pointer;
      }

      ::operator delete(pointer);
    }

    void* const pointer = ::operator new(size + 1);
    unsigned char* const mem = static_cast<unsigned char*>(pointer);
    mem[size] = (size <= UCHAR_MAX) ? static_cast<unsigned char>(size) : 0;
    return pointer;
  }


  static void deallocate(thread_info_base* this_thread,
      void* pointer, std::size_t size)
  {
    if (size <= UCHAR_MAX)
    {
      if (this_thread && this_thread->reusable_memory_ == 0)
      {
        unsigned char* const mem = static_cast<unsigned char*>(pointer);
        mem[0] = mem[size];
        this_thread->reusable_memory_ = pointer;
        return;
      }
    }

    ::operator delete(pointer);
  }

    explicit auto_addrinfo(boost::asio::detail::addrinfo_type* ai)
      : ai_(ai)
    {
    }


    ~auto_addrinfo()
    {
      if (ai_)
        socket_ops::freeaddrinfo(ai_);
    }

  reactive_socket_recvfrom_op_base(socket_type socket, int protocol_type,
      const MutableBufferSequence& buffers, Endpoint& endpoint,
      socket_base::message_flags flags, func_type complete_func)
    : reactor_op(&reactive_socket_recvfrom_op_base::do_perform, complete_func),
      socket_(socket),
      protocol_type_(protocol_type),
      buffers_(buffers),
      sender_endpoint_(endpoint),
      flags_(flags)
  {
  }


  static bool do_perform(reactor_op* base)
  {
    reactive_socket_recvfrom_op_base* o(
        static_cast<reactive_socket_recvfrom_op_base*>(base));

    buffer_sequence_adapter<boost::asio::mutable_buffer,
        MutableBufferSequence> bufs(o->buffers_);

    std::size_t addr_len = o->sender_endpoint_.capacity();
    bool result = socket_ops::non_blocking_recvfrom(o->socket_,
        bufs.buffers(), bufs.count(), o->flags_,
        o->sender_endpoint_.data(), &addr_len,
        o->ec_, o->bytes_transferred_);

    if (result && !o->ec_)
      o->sender_endpoint_.resize(addr_len);

    return result;
  }


  reactive_socket_recvfrom_op(socket_type socket, int protocol_type,
      const MutableBufferSequence& buffers, Endpoint& endpoint,
      socket_base::message_flags flags, Handler& handler)
    : reactive_socket_recvfrom_op_base<MutableBufferSequence, Endpoint>(
        socket, protocol_type, buffers, endpoint, flags,
        &reactive_socket_recvfrom_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler))
  {
  }


  static void do_complete(io_service_impl* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    reactive_socket_recvfrom_op* o(
        static_cast<reactive_socket_recvfrom_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };

    BOOST_ASIO_HANDLER_COMPLETION((o));

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder2<Handler, boost::system::error_code, std::size_t>
      handler(o->handler_, o->ec_, o->bytes_transferred_);
    p.h = boost::asio::detail::addressof(handler.handler_);
    p.reset();

    // Make the upcall if required.
    if (owner)
    {
      fenced_block b(fenced_block::half);
      BOOST_ASIO_HANDLER_INVOCATION_BEGIN((handler.arg1_, handler.arg2_));
      boost_asio_handler_invoke_helpers::invoke(handler, handler.handler_);
      BOOST_ASIO_HANDLER_INVOCATION_END;
    }
  }

  explicit base_from_completion_cond(CompletionCondition completion_condition)
    : completion_condition_(completion_condition)
  {
  }


  std::size_t check_for_completion(
      const boost::system::error_code& ec,
      std::size_t total_transferred)
  {
    return detail::adapt_completion_condition_result(
        completion_condition_(ec, total_transferred));
  }

  signal_op(func_type func)
    : operation(func),
      signal_number_(0)
  {
  }


  completion_handler(Handler& h)
    : operation(&completion_handler::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(h))
  {
  }


  static void do_complete(io_service_impl* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    completion_handler* h(static_cast<completion_handler*>(base));
    ptr p = { boost::asio::detail::addressof(h->handler_), h, h };

    BOOST_ASIO_HANDLER_COMPLETION((h));

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    Handler handler(BOOST_ASIO_MOVE_CAST(Handler)(h->handler_));
    p.h = boost::asio::detail::addressof(handler);
    p.reset();

    // Make the upcall if required.
    if (owner)
    {
      fenced_block b(fenced_block::half);
      BOOST_ASIO_HANDLER_INVOCATION_BEGIN(());
      boost_asio_handler_invoke_helpers::invoke(handler, handler);
      BOOST_ASIO_HANDLER_INVOCATION_END;
    }
  }

  template <typename Object>
  static Object* create()
  {
    return new Object;
  }


  template <typename Object>
  static void destroy(Object* o)
  {
    delete o;
  }


  template <typename Object>
  static Object*& next(Object* o)
  {
    return o->next_;
  }


  template <typename Object>
  static Object*& prev(Object* o)
  {
    return o->prev_;
  }

  object_pool()
    : live_list_(0),
      free_list_(0)
  {
  }

  ~object_pool()
  {
    destroy_list(live_list_);
    destroy_list(free_list_);
  }

  Object* first()
  {
    return live_list_;
  }

  Object* alloc()
  {
    Object* o = free_list_;
    if (o)
      free_list_ = object_pool_access::next(free_list_);
    else
      o = object_pool_access::create<Object>();

    object_pool_access::next(o) = live_list_;
    object_pool_access::prev(o) = 0;
    if (live_list_)
      object_pool_access::prev(live_list_) = o;
    live_list_ = o;

    return o;
  }

  void free(Object* o)
  {
    if (live_list_ == o)
      live_list_ = object_pool_access::next(o);

    if (object_pool_access::prev(o))
    {
      object_pool_access::next(object_pool_access::prev(o))
        = object_pool_access::next(o);
    }

    if (object_pool_access::next(o))
    {
      object_pool_access::prev(object_pool_access::next(o))
        = object_pool_access::prev(o);
    }

    object_pool_access::next(o) = free_list_;
    object_pool_access::prev(o) = 0;
    free_list_ = o;
  }

  void destroy_list(Object* list)
  {
    while (list)
    {
      Object* o = list;
      list = object_pool_access::next(o);
      object_pool_access::destroy(o);
    }
  }

  void post_immediate_completion(reactor_op* op, bool is_continuation)
  {
    io_service_.post_immediate_completion(op, is_continuation);
  }

    per_timer_data() : next_(0), prev_(0) {}

  timer_queue()
    : timers_(),
      heap_()
  {
  }

  bool enqueue_timer(const time_type& time, per_timer_data& timer, wait_op* op)
  {
    // Enqueue the timer object.
    if (timer.prev_ == 0 && &timer != timers_)
    {
      if (this->is_positive_infinity(time))
      {
        // No heap entry is required for timers that never expire.
        timer.heap_index_ = (std::numeric_limits<std::size_t>::max)();
      }
      else
      {
        // Put the new timer at the correct position in the heap. This is done
        // first since push_back() can throw due to allocation failure.
        timer.heap_index_ = heap_.size();
        heap_entry entry = { time, &timer };
        heap_.push_back(entry);
        up_heap(heap_.size() - 1);
      }

      // Insert the new timer into the linked list of active timers.
      timer.next_ = timers_;
      timer.prev_ = 0;
      if (timers_)
        timers_->prev_ = &timer;
      timers_ = &timer;
    }

    // Enqueue the individual timer operation.
    timer.op_queue_.push(op);

    // Interrupt reactor only if newly added timer is first to expire.
    return timer.heap_index_ == 0 && timer.op_queue_.front() == op;
  }

  virtual bool empty() const
  {
    return timers_ == 0;
  }

  virtual long wait_duration_msec(long max_duration) const
  {
    if (heap_.empty())
      return max_duration;

    return this->to_msec(
        Time_Traits::to_posix_duration(
          Time_Traits::subtract(heap_[0].time_, Time_Traits::now())),
        max_duration);
  }

  virtual long wait_duration_usec(long max_duration) const
  {
    if (heap_.empty())
      return max_duration;

    return this->to_usec(
        Time_Traits::to_posix_duration(
          Time_Traits::subtract(heap_[0].time_, Time_Traits::now())),
        max_duration);
  }

  virtual void get_ready_timers(op_queue<operation>& ops)
  {
    if (!heap_.empty())
    {
      const time_type now = Time_Traits::now();
      while (!heap_.empty() && !Time_Traits::less_than(now, heap_[0].time_))
      {
        per_timer_data* timer = heap_[0].timer_;
        ops.push(timer->op_queue_);
        remove_timer(*timer);
      }
    }
  }

  virtual void get_all_timers(op_queue<operation>& ops)
  {
    while (timers_)
    {
      per_timer_data* timer = timers_;
      timers_ = timers_->next_;
      ops.push(timer->op_queue_);
      timer->next_ = 0;
      timer->prev_ = 0;
    }

    heap_.clear();
  }

  std::size_t cancel_timer(per_timer_data& timer, op_queue<operation>& ops,
      std::size_t max_cancelled = (std::numeric_limits<std::size_t>::max)())
  {
    std::size_t num_cancelled = 0;
    if (timer.prev_ != 0 || &timer == timers_)
    {
      while (wait_op* op = (num_cancelled != max_cancelled)
          ? timer.op_queue_.front() : 0)
      {
        op->ec_ = boost::asio::error::operation_aborted;
        timer.op_queue_.pop();
        ops.push(op);
        ++num_cancelled;
      }
      if (timer.op_queue_.empty())
        remove_timer(timer);
    }
    return num_cancelled;
  }

  void up_heap(std::size_t index)
  {
    std::size_t parent = (index - 1) / 2;
    while (index > 0
        && Time_Traits::less_than(heap_[index].time_, heap_[parent].time_))
    {
      swap_heap(index, parent);
      index = parent;
      parent = (index - 1) / 2;
    }
  }

  void down_heap(std::size_t index)
  {
    std::size_t child = index * 2 + 1;
    while (child < heap_.size())
    {
      std::size_t min_child = (child + 1 == heap_.size()
          || Time_Traits::less_than(
            heap_[child].time_, heap_[child + 1].time_))
        ? child : child + 1;
      if (Time_Traits::less_than(heap_[index].time_, heap_[min_child].time_))
        break;
      swap_heap(index, min_child);
      index = min_child;
      child = index * 2 + 1;
    }
  }

  void swap_heap(std::size_t index1, std::size_t index2)
  {
    heap_entry tmp = heap_[index1];
    heap_[index1] = heap_[index2];
    heap_[index2] = tmp;
    heap_[index1].timer_->heap_index_ = index1;
    heap_[index2].timer_->heap_index_ = index2;
  }

  void remove_timer(per_timer_data& timer)
  {
    // Remove the timer from the heap.
    std::size_t index = timer.heap_index_;
    if (!heap_.empty() && index < heap_.size())
    {
      if (index == heap_.size() - 1)
      {
        heap_.pop_back();
      }
      else
      {
        swap_heap(index, heap_.size() - 1);
        heap_.pop_back();
        std::size_t parent = (index - 1) / 2;
        if (index > 0 && Time_Traits::less_than(
              heap_[index].time_, heap_[parent].time_))
          up_heap(index);
        else
          down_heap(index);
      }
    }

    // Remove the timer from the linked list of active timers.
    if (timers_ == &timer)
      timers_ = timer.next_;
    if (timer.prev_)
      timer.prev_->next_ = timer.next_;
    if (timer.next_)
      timer.next_->prev_= timer.prev_;
    timer.next_ = 0;
    timer.prev_ = 0;
  }

  template <typename Time_Type>
  static bool is_positive_infinity(const Time_Type&)
  {
    return false;
  }

  template <typename Duration>
  long to_msec(const Duration& d, long max_duration) const
  {
    if (d.ticks() <= 0)
      return 0;
    int64_t msec = d.total_milliseconds();
    if (msec == 0)
      return 1;
    if (msec > max_duration)
      return max_duration;
    return static_cast<long>(msec);
  }

  template <typename Duration>
  long to_usec(const Duration& d, long max_duration) const
  {
    if (d.ticks() <= 0)
      return 0;
    int64_t usec = d.total_microseconds();
    if (usec == 0)
      return 1;
    if (usec > max_duration)
      return max_duration;
    return static_cast<long>(usec);
  }


  resolve_op(socket_ops::weak_cancel_token_type cancel_token,
      const query_type& query, io_service_impl& ios, Handler& handler)
    : operation(&resolve_op::do_complete),
      cancel_token_(cancel_token),
      query_(query),
      io_service_impl_(ios),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      addrinfo_(0)
  {
  }


  ~resolve_op()
  {
    if (addrinfo_)
      socket_ops::freeaddrinfo(addrinfo_);
  }


  static void do_complete(io_service_impl* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the operation object.
    resolve_op* o(static_cast<resolve_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };

    if (owner && owner != &o->io_service_impl_)
    {
      // The operation is being run on the worker io_service. Time to perform
      // the resolver operation.
    
      // Perform the blocking host resolution operation.
      socket_ops::background_getaddrinfo(o->cancel_token_,
          o->query_.host_name().c_str(), o->query_.service_name().c_str(),
          o->query_.hints(), &o->addrinfo_, o->ec_);

      // Pass operation back to main io_service for completion.
      o->io_service_impl_.post_deferred_completion(o);
      p.v = p.p = 0;
    }
    else
    {
      // The operation has been returned to the main io_service. The completion
      // handler is ready to be delivered.

      BOOST_ASIO_HANDLER_COMPLETION((o));

      // Make a copy of the handler so that the memory can be deallocated
      // before the upcall is made. Even if we're not about to make an upcall,
      // a sub-object of the handler may be the true owner of the memory
      // associated with the handler. Consequently, a local copy of the handler
      // is required to ensure that any owning sub-object remains valid until
      // after we have deallocated the memory here.
      detail::binder2<Handler, boost::system::error_code, iterator_type>
        handler(o->handler_, o->ec_, iterator_type());
      p.h = boost::asio::detail::addressof(handler.handler_);
      if (o->addrinfo_)
      {
        handler.arg2_ = iterator_type::create(o->addrinfo_,
            o->query_.host_name(), o->query_.service_name());
      }
      p.reset();

      if (owner)
      {
        fenced_block b(fenced_block::half);
        BOOST_ASIO_HANDLER_INVOCATION_BEGIN((handler.arg1_, "..."));
        boost_asio_handler_invoke_helpers::invoke(handler, handler.handler_);
        BOOST_ASIO_HANDLER_INVOCATION_END;
      }
    }
  }

  template <typename Dispatcher, typename Handler>
  bool operator()(Dispatcher&, Handler& handler) const
  {
    return boost_asio_handler_cont_helpers::is_continuation(handler);
  }

  template <typename Dispatcher, typename Handler>
  bool operator()(Dispatcher& dispatcher, Handler&) const
  {
    return dispatcher.running_in_this_thread();
  }


  wrapped_handler(Dispatcher dispatcher, Handler& handler)
    : dispatcher_(dispatcher),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler))
  {
  }


  void operator()()
  {
    dispatcher_.dispatch(handler_);
  }


  void operator()() const
  {
    dispatcher_.dispatch(handler_);
  }


  template <typename Arg1>
  void operator()(const Arg1& arg1)
  {
    dispatcher_.dispatch(detail::bind_handler(handler_, arg1));
  }


  template <typename Arg1>
  void operator()(const Arg1& arg1) const
  {
    dispatcher_.dispatch(detail::bind_handler(handler_, arg1));
  }


  template <typename Arg1, typename Arg2>
  void operator()(const Arg1& arg1, const Arg2& arg2)
  {
    dispatcher_.dispatch(detail::bind_handler(handler_, arg1, arg2));
  }


  template <typename Arg1, typename Arg2>
  void operator()(const Arg1& arg1, const Arg2& arg2) const
  {
    dispatcher_.dispatch(detail::bind_handler(handler_, arg1, arg2));
  }


  template <typename Arg1, typename Arg2, typename Arg3>
  void operator()(const Arg1& arg1, const Arg2& arg2, const Arg3& arg3)
  {
    dispatcher_.dispatch(detail::bind_handler(handler_, arg1, arg2, arg3));
  }


  template <typename Arg1, typename Arg2, typename Arg3>
  void operator()(const Arg1& arg1, const Arg2& arg2, const Arg3& arg3) const
  {
    dispatcher_.dispatch(detail::bind_handler(handler_, arg1, arg2, arg3));
  }


  template <typename Arg1, typename Arg2, typename Arg3, typename Arg4>
  void operator()(const Arg1& arg1, const Arg2& arg2, const Arg3& arg3,
      const Arg4& arg4)
  {
    dispatcher_.dispatch(
        detail::bind_handler(handler_, arg1, arg2, arg3, arg4));
  }


  template <typename Arg1, typename Arg2, typename Arg3, typename Arg4>
  void operator()(const Arg1& arg1, const Arg2& arg2, const Arg3& arg3,
      const Arg4& arg4) const
  {
    dispatcher_.dispatch(
        detail::bind_handler(handler_, arg1, arg2, arg3, arg4));
  }


  template <typename Arg1, typename Arg2, typename Arg3, typename Arg4,
      typename Arg5>
  void operator()(const Arg1& arg1, const Arg2& arg2, const Arg3& arg3,
      const Arg4& arg4, const Arg5& arg5)
  {
    dispatcher_.dispatch(
        detail::bind_handler(handler_, arg1, arg2, arg3, arg4, arg5));
  }


  template <typename Arg1, typename Arg2, typename Arg3, typename Arg4,
      typename Arg5>
  void operator()(const Arg1& arg1, const Arg2& arg2, const Arg3& arg3,
      const Arg4& arg4, const Arg5& arg5) const
  {
    dispatcher_.dispatch(
        detail::bind_handler(handler_, arg1, arg2, arg3, arg4, arg5));
  }

  explicit rewrapped_handler(Handler& handler, const Context& context)
    : context_(context),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler))
  {
  }


  explicit rewrapped_handler(const Handler& handler, const Context& context)
    : context_(context),
      handler_(handler)
  {
  }


  void operator()()
  {
    handler_();
  }


  void operator()() const
  {
    handler_();
  }


template <typename Dispatcher, typename Handler, typename IsContinuation>
inline void* asio_handler_allocate(std::size_t size,
    wrapped_handler<Dispatcher, Handler, IsContinuation>* this_handler)
{
  return boost_asio_handler_alloc_helpers::allocate(
      size, this_handler->handler_);
}


template <typename Dispatcher, typename Handler, typename IsContinuation>
inline void asio_handler_deallocate(void* pointer, std::size_t size,
    wrapped_handler<Dispatcher, Handler, IsContinuation>* this_handler)
{
  boost_asio_handler_alloc_helpers::deallocate(
      pointer, size, this_handler->handler_);
}


template <typename Dispatcher, typename Handler, typename IsContinuation>
inline bool asio_handler_is_continuation(
    wrapped_handler<Dispatcher, Handler, IsContinuation>* this_handler)
{
  return IsContinuation()(this_handler->dispatcher_, this_handler->handler_);
}


template <typename Function, typename Dispatcher,
    typename Handler, typename IsContinuation>
inline void asio_handler_invoke(Function& function,
    wrapped_handler<Dispatcher, Handler, IsContinuation>* this_handler)
{
  this_handler->dispatcher_.dispatch(
      rewrapped_handler<Function, Handler>(
        function, this_handler->handler_));
}


template <typename Function, typename Dispatcher,
    typename Handler, typename IsContinuation>
inline void asio_handler_invoke(const Function& function,
    wrapped_handler<Dispatcher, Handler, IsContinuation>* this_handler)
{
  this_handler->dispatcher_.dispatch(
      rewrapped_handler<Function, Handler>(
        function, this_handler->handler_));
}


template <typename Dispatcher, typename Context>
inline bool asio_handler_is_continuation(
    rewrapped_handler<Dispatcher, Context>* this_handler)
{
  return boost_asio_handler_cont_helpers::is_continuation(
      this_handler->handler_);
}


template <typename Function, typename Handler, typename Context>
inline void asio_handler_invoke(Function& function,
    rewrapped_handler<Handler, Context>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->context_);
}


template <typename Function, typename Handler, typename Context>
inline void asio_handler_invoke(const Function& function,
    rewrapped_handler<Handler, Context>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->context_);
}

  timer_queue_base() : next_(0) {}

  virtual ~timer_queue_base() {}

  template <typename Function>
  null_thread(Function, unsigned int = 0)
  {
    boost::asio::detail::throw_error(
        boost::asio::error::operation_not_supported, "thread");
  }

  ~null_thread()
  {
  }

  void join()
  {
  }

  reactive_socket_connect_op_base(socket_type socket,
      const typename Protocol::endpoint& peer_endpoint, func_type complete_func)
    : reactor_op(&reactive_socket_connect_op_base::do_perform, complete_func),
      socket_(socket),
      peer_endpoint_(peer_endpoint)
  {
  }


  static bool do_perform(reactor_op* base)
  {
    reactive_socket_connect_op_base* o(
        static_cast<reactive_socket_connect_op_base*>(base));

    return socket_ops::non_blocking_connect(o->socket_,
        o->peer_endpoint_.data(), o->peer_endpoint_.size(), o->ec_);
  }


  reactive_socket_connect_op(socket_type socket,
      const typename Protocol::endpoint& peer_endpoint, Handler& handler)
    : reactive_socket_connect_op_base<Protocol>(socket, peer_endpoint,
        &reactive_socket_connect_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler))
  {
  }


  static void do_complete(io_service_impl* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    reactive_socket_connect_op* o
      (static_cast<reactive_socket_connect_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };

    BOOST_ASIO_HANDLER_COMPLETION((o));

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder1<Handler, boost::system::error_code>
      handler(o->handler_, o->ec_);
    p.h = boost::asio::detail::addressof(handler.handler_);
    p.reset();

    // Make the upcall if required.
    if (owner)
    {
      fenced_block b(fenced_block::half);
      BOOST_ASIO_HANDLER_INVOCATION_BEGIN((handler.arg1_));
      boost_asio_handler_invoke_helpers::invoke(handler, handler);
      BOOST_ASIO_HANDLER_INVOCATION_END;
    }
  }

  reactor_op_queue()
    : operations_()
  {
  }

  bool enqueue_operation(Descriptor descriptor, reactor_op* op)
  {
    typedef typename operations_map::iterator iterator;
    typedef typename operations_map::value_type value_type;
    std::pair<iterator, bool> entry =
      operations_.insert(value_type(descriptor, operations()));
    entry.first->second.op_queue_.push(op);
    return entry.second;
  }

  bool cancel_operations(Descriptor descriptor, op_queue<operation>& ops,
      const boost::system::error_code& ec =
        boost::asio::error::operation_aborted)
  {
    typename operations_map::iterator i = operations_.find(descriptor);
    if (i != operations_.end())
    {
      while (reactor_op* op = i->second.op_queue_.front())
      {
        op->ec_ = ec;
        i->second.op_queue_.pop();
        ops.push(op);
      }
      operations_.erase(i);
      return true;
    }

    return false;
  }

  bool empty() const
  {
    return operations_.empty();
  }

  bool has_operation(Descriptor descriptor) const
  {
    return operations_.find(descriptor) != operations_.end();
  }

  bool perform_operations(Descriptor descriptor, op_queue<operation>& ops)
  {
    typename operations_map::iterator i = operations_.find(descriptor);
    if (i != operations_.end())
    {
      while (reactor_op* op = i->second.op_queue_.front())
      {
        if (op->perform())
        {
          i->second.op_queue_.pop();
          ops.push(op);
        }
        else
        {
          return true;
        }
      }
      operations_.erase(i);
    }
    return false;
  }

  template <typename Descriptor_Set>
  void get_descriptors(Descriptor_Set& descriptors, op_queue<operation>& ops)
  {
    typename operations_map::iterator i = operations_.begin();
    while (i != operations_.end())
    {
      Descriptor descriptor = i->first;
      ++i;
      if (!descriptors.set(descriptor))
      {
        boost::system::error_code ec(error::fd_set_failure);
        cancel_operations(descriptor, ops, ec);
      }
    }
  }

  template <typename Descriptor_Set>
  void perform_operations_for_descriptors(
      const Descriptor_Set& descriptors, op_queue<operation>& ops)
  {
    typename operations_map::iterator i = operations_.begin();
    while (i != operations_.end())
    {
      typename operations_map::iterator op_iter = i++;
      if (descriptors.is_set(op_iter->first))
      {
        while (reactor_op* op = op_iter->second.op_queue_.front())
        {
          if (op->perform())
          {
            op_iter->second.op_queue_.pop();
            ops.push(op);
          }
          else
          {
            break;
          }
        }

        if (op_iter->second.op_queue_.empty())
          operations_.erase(op_iter);
      }
    }
  }

  void get_all_operations(op_queue<operation>& ops)
  {
    typename operations_map::iterator i = operations_.begin();
    while (i != operations_.end())
    {
      typename operations_map::iterator op_iter = i++;
      ops.push(op_iter->second.op_queue_);
      operations_.erase(op_iter);
    }
  }

    operations() {}

    operations(const operations&) {}

    void operator=(const operations&) {}

  explicit gcc_sync_fenced_block(half_or_full_t)
    : value_(0)
  {
    __sync_lock_test_and_set(&value_, 1);
  }

  ~gcc_sync_fenced_block()
  {
    __sync_lock_release(&value_);
  }

  scoped_lock(Mutex& m, adopt_lock_t)
    : mutex_(m),
      locked_(true)
  {
  }

  explicit scoped_lock(Mutex& m)
    : mutex_(m)
  {
    mutex_.lock();
    locked_ = true;
  }

  ~scoped_lock()
  {
    if (locked_)
      mutex_.unlock();
  }

  void lock()
  {
    if (!locked_)
    {
      mutex_.lock();
      locked_ = true;
    }
  }

  void unlock()
  {
    if (locked_)
    {
      mutex_.unlock();
      locked_ = false;
    }
  }

  bool locked() const
  {
    return locked_;
  }

  Mutex& mutex()
  {
    return mutex_;
  }

  reactive_socket_recv_op_base(socket_type socket,
      socket_ops::state_type state, const MutableBufferSequence& buffers,
      socket_base::message_flags flags, func_type complete_func)
    : reactor_op(&reactive_socket_recv_op_base::do_perform, complete_func),
      socket_(socket),
      state_(state),
      buffers_(buffers),
      flags_(flags)
  {
  }


  static bool do_perform(reactor_op* base)
  {
    reactive_socket_recv_op_base* o(
        static_cast<reactive_socket_recv_op_base*>(base));

    buffer_sequence_adapter<boost::asio::mutable_buffer,
        MutableBufferSequence> bufs(o->buffers_);

    return socket_ops::non_blocking_recv(o->socket_,
        bufs.buffers(), bufs.count(), o->flags_,
        (o->state_ & socket_ops::stream_oriented) != 0,
        o->ec_, o->bytes_transferred_);
  }


  reactive_socket_recv_op(socket_type socket,
      socket_ops::state_type state, const MutableBufferSequence& buffers,
      socket_base::message_flags flags, Handler& handler)
    : reactive_socket_recv_op_base<MutableBufferSequence>(socket, state,
        buffers, flags, &reactive_socket_recv_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler))
  {
  }


  static void do_complete(io_service_impl* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    reactive_socket_recv_op* o(static_cast<reactive_socket_recv_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };

    BOOST_ASIO_HANDLER_COMPLETION((o));

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder2<Handler, boost::system::error_code, std::size_t>
      handler(o->handler_, o->ec_, o->bytes_transferred_);
    p.h = boost::asio::detail::addressof(handler.handler_);
    p.reset();

    // Make the upcall if required.
    if (owner)
    {
      fenced_block b(fenced_block::half);
      BOOST_ASIO_HANDLER_INVOCATION_BEGIN((handler.arg1_, handler.arg2_));
      boost_asio_handler_invoke_helpers::invoke(handler, handler.handler_);
      BOOST_ASIO_HANDLER_INVOCATION_END;
    }
  }

  signal_init()
  {
    std::signal(Signal, SIG_IGN);
  }


template <typename SyncRandomAccessWriteDevice, typename ConstBufferSequence,
    typename CompletionCondition>
std::size_t write_at(SyncRandomAccessWriteDevice& d,
    uint64_t offset, const ConstBufferSequence& buffers,
    CompletionCondition completion_condition, boost::system::error_code& ec)
{
  ec = boost::system::error_code();
  boost::asio::detail::consuming_buffers<
    const_buffer, ConstBufferSequence> tmp(buffers);
  std::size_t total_transferred = 0;
  tmp.prepare(detail::adapt_completion_condition_result(
        completion_condition(ec, total_transferred)));
  while (tmp.begin() != tmp.end())
  {
    std::size_t bytes_transferred = d.write_some_at(
        offset + total_transferred, tmp, ec);
    tmp.consume(bytes_transferred);
    total_transferred += bytes_transferred;
    tmp.prepare(detail::adapt_completion_condition_result(
          completion_condition(ec, total_transferred)));
  }
  return total_transferred;
}

    write_at_op(AsyncRandomAccessWriteDevice& device,
        uint64_t offset, const ConstBufferSequence& buffers,
        CompletionCondition completion_condition, WriteHandler& handler)
      : detail::base_from_completion_cond<
          CompletionCondition>(completion_condition),
        device_(device),
        offset_(offset),
        buffers_(buffers),
        start_(0),
        total_transferred_(0),
        handler_(BOOST_ASIO_MOVE_CAST(WriteHandler)(handler))
    {
    }


    void operator()(const boost::system::error_code& ec,
        std::size_t bytes_transferred, int start = 0)
    {
      switch (start_ = start)
      {
        case 1:
        buffers_.prepare(this->check_for_completion(ec, total_transferred_));
        for (;;)
        {
          device_.async_write_some_at(
              offset_ + total_transferred_, buffers_,
              BOOST_ASIO_MOVE_CAST(write_at_op)(*this));
          return; default:
          total_transferred_ += bytes_transferred;
          buffers_.consume(bytes_transferred);
          buffers_.prepare(this->check_for_completion(ec, total_transferred_));
          if ((!ec && bytes_transferred == 0)
              || buffers_.begin() == buffers_.end())
            break;
        }

        handler_(ec, static_cast<const std::size_t&>(total_transferred_));
      }
    }


  template <typename AsyncRandomAccessWriteDevice, typename ConstBufferSequence,
      typename CompletionCondition, typename WriteHandler>
  inline void* asio_handler_allocate(std::size_t size,
      write_at_op<AsyncRandomAccessWriteDevice, ConstBufferSequence,
        CompletionCondition, WriteHandler>* this_handler)
  {
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
  }


  template <typename AsyncRandomAccessWriteDevice, typename ConstBufferSequence,
      typename CompletionCondition, typename WriteHandler>
  inline void asio_handler_deallocate(void* pointer, std::size_t size,
      write_at_op<AsyncRandomAccessWriteDevice, ConstBufferSequence,
        CompletionCondition, WriteHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
  }


  template <typename AsyncRandomAccessWriteDevice, typename ConstBufferSequence,
      typename CompletionCondition, typename WriteHandler>
  inline bool asio_handler_is_continuation(
      write_at_op<AsyncRandomAccessWriteDevice, ConstBufferSequence,
        CompletionCondition, WriteHandler>* this_handler)
  {
    return this_handler->start_ == 0 ? true
      : boost_asio_handler_cont_helpers::is_continuation(
          this_handler->handler_);
  }


  template <typename Function, typename AsyncRandomAccessWriteDevice,
      typename ConstBufferSequence, typename CompletionCondition,
      typename WriteHandler>
  inline void asio_handler_invoke(Function& function,
      write_at_op<AsyncRandomAccessWriteDevice, ConstBufferSequence,
        CompletionCondition, WriteHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }


  template <typename Function, typename AsyncRandomAccessWriteDevice,
      typename ConstBufferSequence, typename CompletionCondition,
      typename WriteHandler>
  inline void asio_handler_invoke(const Function& function,
      write_at_op<AsyncRandomAccessWriteDevice, ConstBufferSequence,
        CompletionCondition, WriteHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }


  template <typename AsyncRandomAccessWriteDevice, typename ConstBufferSequence,
      typename CompletionCondition, typename WriteHandler>
  inline write_at_op<AsyncRandomAccessWriteDevice,
      ConstBufferSequence, CompletionCondition, WriteHandler>
  make_write_at_op(AsyncRandomAccessWriteDevice& d,
      uint64_t offset, const ConstBufferSequence& buffers,
      CompletionCondition completion_condition, WriteHandler handler)
  {
    return write_at_op<AsyncRandomAccessWriteDevice,
      ConstBufferSequence, CompletionCondition, WriteHandler>(
        d, offset, buffers, completion_condition, handler);
  }

async_write_at(AsyncRandomAccessWriteDevice& d,
    uint64_t offset, const ConstBufferSequence& buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(WriteHandler) handler)
{
  // If you get an error on the following line it means that your handler does
  // not meet the documented type requirements for a WriteHandler.
  BOOST_ASIO_WRITE_HANDLER_CHECK(WriteHandler, handler) type_check;

  detail::async_result_init<
    WriteHandler, void (boost::system::error_code, std::size_t)> init(
      BOOST_ASIO_MOVE_CAST(WriteHandler)(handler));

  detail::write_at_op<AsyncRandomAccessWriteDevice, ConstBufferSequence,
    CompletionCondition, BOOST_ASIO_HANDLER_TYPE(
      WriteHandler, void (boost::system::error_code, std::size_t))>(
        d, offset, buffers, completion_condition, init.handler)(
          boost::system::error_code(), 0, 1);

  return init.result.get();
}

    write_at_streambuf_op(
        boost::asio::basic_streambuf<Allocator>& streambuf,
        WriteHandler& handler)
      : streambuf_(streambuf),
        handler_(BOOST_ASIO_MOVE_CAST(WriteHandler)(handler))
    {
    }


    void operator()(const boost::system::error_code& ec,
        const std::size_t bytes_transferred)
    {
      streambuf_.consume(bytes_transferred);
      handler_(ec, bytes_transferred);
    }


  template <typename Allocator, typename WriteHandler>
  inline bool asio_handler_is_continuation(
      write_at_streambuf_op<Allocator, WriteHandler>* this_handler)
  {
    return boost_asio_handler_cont_helpers::is_continuation(
        this_handler->handler_);
  }


  template <typename Function, typename Allocator, typename WriteHandler>
  inline void asio_handler_invoke(Function& function,
      write_at_streambuf_op<Allocator, WriteHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }


  template <typename Function, typename Allocator, typename WriteHandler>
  inline void asio_handler_invoke(const Function& function,
      write_at_streambuf_op<Allocator, WriteHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

    template <typename Iterator>
    Iterator operator()(const boost::system::error_code&, Iterator next)
    {
      return next;
    }

    explicit base_from_connect_condition(
        const ConnectCondition& connect_condition)
      : connect_condition_(connect_condition)
    {
    }


    template <typename Iterator>
    void check_condition(const boost::system::error_code& ec,
        Iterator& iter, Iterator& end)
    {
      if (iter != end)
        iter = connect_condition_(ec, static_cast<const Iterator&>(iter));
    }

    explicit base_from_connect_condition(const default_connect_condition&)
    {
    }


    template <typename Iterator>
    void check_condition(const boost::system::error_code&, Iterator&, Iterator&)
    {
    }

    connect_op(basic_socket<Protocol, SocketService>& sock,
        const Iterator& begin, const Iterator& end,
        const ConnectCondition& connect_condition,
        ComposedConnectHandler& handler)
      : base_from_connect_condition<ConnectCondition>(connect_condition),
        socket_(sock),
        iter_(begin),
        end_(end),
        start_(0),
        handler_(BOOST_ASIO_MOVE_CAST(ComposedConnectHandler)(handler))
    {
    }


    void operator()(boost::system::error_code ec, int start = 0)
    {
      switch (start_ = start)
      {
        case 1:
        for (;;)
        {
          this->check_condition(ec, iter_, end_);

          if (iter_ != end_)
          {
            socket_.close(ec);
            socket_.async_connect(*iter_,
                BOOST_ASIO_MOVE_CAST(connect_op)(*this));
            return;
          }

          if (start)
          {
            ec = boost::asio::error::not_found;
            socket_.get_io_service().post(detail::bind_handler(*this, ec));
            return;
          }

          default:

          if (iter_ == end_)
            break;

          if (!socket_.is_open())
          {
            ec = boost::asio::error::operation_aborted;
            break;
          }

          if (!ec)
            break;

          ++iter_;
        }

        handler_(static_cast<const boost::system::error_code&>(ec),
            static_cast<const Iterator&>(iter_));
      }
    }


  template <typename Protocol, typename SocketService, typename Iterator,
      typename ConnectCondition, typename ComposedConnectHandler>
  inline void* asio_handler_allocate(std::size_t size,
      connect_op<Protocol, SocketService, Iterator,
        ConnectCondition, ComposedConnectHandler>* this_handler)
  {
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
  }


  template <typename Protocol, typename SocketService, typename Iterator,
      typename ConnectCondition, typename ComposedConnectHandler>
  inline void asio_handler_deallocate(void* pointer, std::size_t size,
      connect_op<Protocol, SocketService, Iterator,
        ConnectCondition, ComposedConnectHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
  }


  template <typename Protocol, typename SocketService, typename Iterator,
      typename ConnectCondition, typename ComposedConnectHandler>
  inline bool asio_handler_is_continuation(
      connect_op<Protocol, SocketService, Iterator,
        ConnectCondition, ComposedConnectHandler>* this_handler)
  {
    return boost_asio_handler_cont_helpers::is_continuation(
        this_handler->handler_);
  }


  template <typename Function, typename Protocol,
      typename SocketService, typename Iterator,
      typename ConnectCondition, typename ComposedConnectHandler>
  inline void asio_handler_invoke(Function& function,
      connect_op<Protocol, SocketService, Iterator,
        ConnectCondition, ComposedConnectHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }


  template <typename Function, typename Protocol,
      typename SocketService, typename Iterator,
      typename ConnectCondition, typename ComposedConnectHandler>
  inline void asio_handler_invoke(const Function& function,
      connect_op<Protocol, SocketService, Iterator,
        ConnectCondition, ComposedConnectHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }


template <typename SyncReadStream, typename Allocator>
inline std::size_t read_until(SyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b, char delim)
{
  boost::system::error_code ec;
  std::size_t bytes_transferred = read_until(s, b, delim, ec);
  boost::asio::detail::throw_error(ec, "read_until");
  return bytes_transferred;
}

    read_until_delim_op(AsyncReadStream& stream,
        boost::asio::basic_streambuf<Allocator>& streambuf,
        char delim, ReadHandler& handler)
      : stream_(stream),
        streambuf_(streambuf),
        delim_(delim),
        start_(0),
        search_position_(0),
        handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(handler))
    {
    }


    void operator()(const boost::system::error_code& ec,
        std::size_t bytes_transferred, int start = 0)
    {
      const std::size_t not_found = (std::numeric_limits<std::size_t>::max)();
      std::size_t bytes_to_read;
      switch (start_ = start)
      {
      case 1:
        for (;;)
        {
          {
            // Determine the range of the data to be searched.
            typedef typename boost::asio::basic_streambuf<
              Allocator>::const_buffers_type const_buffers_type;
            typedef boost::asio::buffers_iterator<const_buffers_type> iterator;
            const_buffers_type buffers = streambuf_.data();
            iterator begin = iterator::begin(buffers);
            iterator start_pos = begin + search_position_;
            iterator end = iterator::end(buffers);

            // Look for a match.
            iterator iter = std::find(start_pos, end, delim_);
            if (iter != end)
            {
              // Found a match. We're done.
              search_position_ = iter - begin + 1;
              bytes_to_read = 0;
            }

            // No match yet. Check if buffer is full.
            else if (streambuf_.size() == streambuf_.max_size())
            {
              search_position_ = not_found;
              bytes_to_read = 0;
            }

            // Need to read some more data.
            else
            {
              // Next search can start with the new data.
              search_position_ = end - begin;
              bytes_to_read = read_size_helper(streambuf_, 65536);
            }
          }

          // Check if we're done.
          if (!start && bytes_to_read == 0)
            break;

          // Start a new asynchronous read operation to obtain more data.
          stream_.async_read_some(streambuf_.prepare(bytes_to_read),
              BOOST_ASIO_MOVE_CAST(read_until_delim_op)(*this));
          return; default:
          streambuf_.commit(bytes_transferred);
          if (ec || bytes_transferred == 0)
            break;
        }

        const boost::system::error_code result_ec =
          (search_position_ == not_found)
          ? error::not_found : ec;

        const std::size_t result_n =
          (ec || search_position_ == not_found)
          ? 0 : search_position_;

        handler_(result_ec, result_n);
      }
    }


  template <typename AsyncReadStream, typename Allocator, typename ReadHandler>
  inline void* asio_handler_allocate(std::size_t size,
      read_until_delim_op<AsyncReadStream,
        Allocator, ReadHandler>* this_handler)
  {
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
  }


  template <typename AsyncReadStream, typename Allocator, typename ReadHandler>
  inline void asio_handler_deallocate(void* pointer, std::size_t size,
      read_until_delim_op<AsyncReadStream,
        Allocator, ReadHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
  }


  template <typename AsyncReadStream, typename Allocator, typename ReadHandler>
  inline bool asio_handler_is_continuation(
      read_until_delim_op<AsyncReadStream,
        Allocator, ReadHandler>* this_handler)
  {
    return this_handler->start_ == 0 ? true
      : boost_asio_handler_cont_helpers::is_continuation(
          this_handler->handler_);
  }


  template <typename Function, typename AsyncReadStream, typename Allocator,
      typename ReadHandler>
  inline void asio_handler_invoke(Function& function,
      read_until_delim_op<AsyncReadStream,
        Allocator, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }


  template <typename Function, typename AsyncReadStream, typename Allocator,
      typename ReadHandler>
  inline void asio_handler_invoke(const Function& function,
      read_until_delim_op<AsyncReadStream,
        Allocator, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }


template <typename Service>
inline Service& use_service(io_service& ios)
{
  // Check that Service meets the necessary type requirements.
  (void)static_cast<io_service::service*>(static_cast<Service*>(0));
  (void)static_cast<const io_service::id*>(&Service::id);

  return ios.service_registry_->template use_service<Service>();
}


template <typename SyncReadStream, typename MutableBufferSequence,
    typename CompletionCondition>
std::size_t read(SyncReadStream& s, const MutableBufferSequence& buffers,
    CompletionCondition completion_condition, boost::system::error_code& ec)
{
  ec = boost::system::error_code();
  boost::asio::detail::consuming_buffers<
    mutable_buffer, MutableBufferSequence> tmp(buffers);
  std::size_t total_transferred = 0;
  tmp.prepare(detail::adapt_completion_condition_result(
        completion_condition(ec, total_transferred)));
  while (tmp.begin() != tmp.end())
  {
    std::size_t bytes_transferred = s.read_some(tmp, ec);
    tmp.consume(bytes_transferred);
    total_transferred += bytes_transferred;
    tmp.prepare(detail::adapt_completion_condition_result(
          completion_condition(ec, total_transferred)));
  }
  return total_transferred;
}

    read_op(AsyncReadStream& stream, const MutableBufferSequence& buffers,
        CompletionCondition completion_condition, ReadHandler& handler)
      : detail::base_from_completion_cond<
          CompletionCondition>(completion_condition),
        stream_(stream),
        buffers_(buffers),
        start_(0),
        total_transferred_(0),
        handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(handler))
    {
    }


    void operator()(const boost::system::error_code& ec,
        std::size_t bytes_transferred, int start = 0)
    {
      switch (start_ = start)
      {
        case 1:
        buffers_.prepare(this->check_for_completion(ec, total_transferred_));
        for (;;)
        {
          stream_.async_read_some(buffers_,
              BOOST_ASIO_MOVE_CAST(read_op)(*this));
          return; default:
          total_transferred_ += bytes_transferred;
          buffers_.consume(bytes_transferred);
          buffers_.prepare(this->check_for_completion(ec, total_transferred_));
          if ((!ec && bytes_transferred == 0)
              || buffers_.begin() == buffers_.end())
            break;
        }

        handler_(ec, static_cast<const std::size_t&>(total_transferred_));
      }
    }


  template <typename AsyncReadStream, typename MutableBufferSequence,
      typename CompletionCondition, typename ReadHandler>
  inline void* asio_handler_allocate(std::size_t size,
      read_op<AsyncReadStream, MutableBufferSequence,
        CompletionCondition, ReadHandler>* this_handler)
  {
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
  }


  template <typename AsyncReadStream, typename MutableBufferSequence,
      typename CompletionCondition, typename ReadHandler>
  inline void asio_handler_deallocate(void* pointer, std::size_t size,
      read_op<AsyncReadStream, MutableBufferSequence,
        CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
  }


  template <typename AsyncReadStream, typename MutableBufferSequence,
      typename CompletionCondition, typename ReadHandler>
  inline bool asio_handler_is_continuation(
      read_op<AsyncReadStream, MutableBufferSequence,
        CompletionCondition, ReadHandler>* this_handler)
  {
    return this_handler->start_ == 0 ? true
      : boost_asio_handler_cont_helpers::is_continuation(
          this_handler->handler_);
  }


  template <typename Function, typename AsyncReadStream,
      typename MutableBufferSequence, typename CompletionCondition,
      typename ReadHandler>
  inline void asio_handler_invoke(Function& function,
      read_op<AsyncReadStream, MutableBufferSequence,
        CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }


  template <typename Function, typename AsyncReadStream,
      typename MutableBufferSequence, typename CompletionCondition,
      typename ReadHandler>
  inline void asio_handler_invoke(const Function& function,
      read_op<AsyncReadStream, MutableBufferSequence,
        CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

async_read(AsyncReadStream& s, const MutableBufferSequence& buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler)
{
  // If you get an error on the following line it means that your handler does
  // not meet the documented type requirements for a ReadHandler.
  BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;

  detail::async_result_init<
    ReadHandler, void (boost::system::error_code, std::size_t)> init(
      BOOST_ASIO_MOVE_CAST(ReadHandler)(handler));

  detail::read_op<AsyncReadStream, MutableBufferSequence,
    CompletionCondition, BOOST_ASIO_HANDLER_TYPE(
      ReadHandler, void (boost::system::error_code, std::size_t))>(
        s, buffers, completion_condition, init.handler)(
          boost::system::error_code(), 0, 1);

  return init.result.get();
}

    read_streambuf_op(AsyncReadStream& stream,
        basic_streambuf<Allocator>& streambuf,
        CompletionCondition completion_condition, ReadHandler& handler)
      : detail::base_from_completion_cond<
          CompletionCondition>(completion_condition),
        stream_(stream),
        streambuf_(streambuf),
        start_(0),
        total_transferred_(0),
        handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(handler))
    {
    }


    void operator()(const boost::system::error_code& ec,
        std::size_t bytes_transferred, int start = 0)
    {
      std::size_t max_size, bytes_available;
      switch (start_ = start)
      {
        case 1:
        max_size = this->check_for_completion(ec, total_transferred_);
        bytes_available = read_size_helper(streambuf_, max_size);
        for (;;)
        {
          stream_.async_read_some(streambuf_.prepare(bytes_available),
              BOOST_ASIO_MOVE_CAST(read_streambuf_op)(*this));
          return; default:
          total_transferred_ += bytes_transferred;
          streambuf_.commit(bytes_transferred);
          max_size = this->check_for_completion(ec, total_transferred_);
          bytes_available = read_size_helper(streambuf_, max_size);
          if ((!ec && bytes_transferred == 0) || bytes_available == 0)
            break;
        }

        handler_(ec, static_cast<const std::size_t&>(total_transferred_));
      }
    }


  template <typename AsyncReadStream, typename Allocator,
      typename CompletionCondition, typename ReadHandler>
  inline bool asio_handler_is_continuation(
      read_streambuf_op<AsyncReadStream, Allocator,
        CompletionCondition, ReadHandler>* this_handler)
  {
    return this_handler->start_ == 0 ? true
      : boost_asio_handler_cont_helpers::is_continuation(
          this_handler->handler_);
  }


  template <typename Function, typename AsyncReadStream,
      typename Allocator, typename CompletionCondition, typename ReadHandler>
  inline void asio_handler_invoke(Function& function,
      read_streambuf_op<AsyncReadStream, Allocator,
        CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }


  template <typename Function, typename AsyncReadStream,
      typename Allocator, typename CompletionCondition, typename ReadHandler>
  inline void asio_handler_invoke(const Function& function,
      read_streambuf_op<AsyncReadStream, Allocator,
        CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }


template <typename SyncWriteStream, typename ConstBufferSequence,
    typename CompletionCondition>
std::size_t write(SyncWriteStream& s, const ConstBufferSequence& buffers,
    CompletionCondition completion_condition, boost::system::error_code& ec)
{
  ec = boost::system::error_code();
  boost::asio::detail::consuming_buffers<
    const_buffer, ConstBufferSequence> tmp(buffers);
  std::size_t total_transferred = 0;
  tmp.prepare(detail::adapt_completion_condition_result(
        completion_condition(ec, total_transferred)));
  while (tmp.begin() != tmp.end())
  {
    std::size_t bytes_transferred = s.write_some(tmp, ec);
    tmp.consume(bytes_transferred);
    total_transferred += bytes_transferred;
    tmp.prepare(detail::adapt_completion_condition_result(
          completion_condition(ec, total_transferred)));
  }
  return total_transferred;
}

    write_op(AsyncWriteStream& stream, const ConstBufferSequence& buffers,
        CompletionCondition completion_condition, WriteHandler& handler)
      : detail::base_from_completion_cond<
          CompletionCondition>(completion_condition),
        stream_(stream),
        buffers_(buffers),
        start_(0),
        total_transferred_(0),
        handler_(BOOST_ASIO_MOVE_CAST(WriteHandler)(handler))
    {
    }


    void operator()(const boost::system::error_code& ec,
        std::size_t bytes_transferred, int start = 0)
    {
      switch (start_ = start)
      {
        case 1:
        buffers_.prepare(this->check_for_completion(ec, total_transferred_));
        for (;;)
        {
          stream_.async_write_some(buffers_,
              BOOST_ASIO_MOVE_CAST(write_op)(*this));
          return; default:
          total_transferred_ += bytes_transferred;
          buffers_.consume(bytes_transferred);
          buffers_.prepare(this->check_for_completion(ec, total_transferred_));
          if ((!ec && bytes_transferred == 0)
              || buffers_.begin() == buffers_.end())
            break;
        }

        handler_(ec, static_cast<const std::size_t&>(total_transferred_));
      }
    }


  template <typename AsyncWriteStream, typename ConstBufferSequence,
      typename CompletionCondition, typename WriteHandler>
  inline void* asio_handler_allocate(std::size_t size,
      write_op<AsyncWriteStream, ConstBufferSequence,
        CompletionCondition, WriteHandler>* this_handler)
  {
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
  }


  template <typename AsyncWriteStream, typename ConstBufferSequence,
      typename CompletionCondition, typename WriteHandler>
  inline void asio_handler_deallocate(void* pointer, std::size_t size,
      write_op<AsyncWriteStream, ConstBufferSequence,
        CompletionCondition, WriteHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
  }


  template <typename AsyncWriteStream, typename ConstBufferSequence,
      typename CompletionCondition, typename WriteHandler>
  inline bool asio_handler_is_continuation(
      write_op<AsyncWriteStream, ConstBufferSequence,
        CompletionCondition, WriteHandler>* this_handler)
  {
    return this_handler->start_ == 0 ? true
      : boost_asio_handler_cont_helpers::is_continuation(
          this_handler->handler_);
  }


  template <typename Function, typename AsyncWriteStream,
      typename ConstBufferSequence, typename CompletionCondition,
      typename WriteHandler>
  inline void asio_handler_invoke(Function& function,
      write_op<AsyncWriteStream, ConstBufferSequence,
        CompletionCondition, WriteHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }


  template <typename Function, typename AsyncWriteStream,
      typename ConstBufferSequence, typename CompletionCondition,
      typename WriteHandler>
  inline void asio_handler_invoke(const Function& function,
      write_op<AsyncWriteStream, ConstBufferSequence,
        CompletionCondition, WriteHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

async_write(AsyncWriteStream& s, const ConstBufferSequence& buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(WriteHandler) handler)
{
  // If you get an error on the following line it means that your handler does
  // not meet the documented type requirements for a WriteHandler.
  BOOST_ASIO_WRITE_HANDLER_CHECK(WriteHandler, handler) type_check;

  detail::async_result_init<
    WriteHandler, void (boost::system::error_code, std::size_t)> init(
      BOOST_ASIO_MOVE_CAST(WriteHandler)(handler));

  detail::write_op<AsyncWriteStream, ConstBufferSequence,
    CompletionCondition, BOOST_ASIO_HANDLER_TYPE(
      WriteHandler, void (boost::system::error_code, std::size_t))>(
        s, buffers, completion_condition, init.handler)(
          boost::system::error_code(), 0, 1);

  return init.result.get();
}

    write_streambuf_handler(boost::asio::basic_streambuf<Allocator>& streambuf,
        WriteHandler& handler)
      : streambuf_(streambuf),
        handler_(BOOST_ASIO_MOVE_CAST(WriteHandler)(handler))
    {
    }


    void operator()(const boost::system::error_code& ec,
        const std::size_t bytes_transferred)
    {
      streambuf_.consume(bytes_transferred);
      handler_(ec, bytes_transferred);
    }


  template <typename Allocator, typename WriteHandler>
  inline bool asio_handler_is_continuation(
      write_streambuf_handler<Allocator, WriteHandler>* this_handler)
  {
    return boost_asio_handler_cont_helpers::is_continuation(
        this_handler->handler_);
  }


  template <typename Function, typename Allocator, typename WriteHandler>
  inline void asio_handler_invoke(Function& function,
      write_streambuf_handler<Allocator, WriteHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }


  template <typename Function, typename Allocator, typename WriteHandler>
  inline void asio_handler_invoke(const Function& function,
      write_streambuf_handler<Allocator, WriteHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

    template <typename Allocator>
    promise_handler(use_future_t<Allocator> uf)
      : promise_(std::allocate_shared<std::promise<T> >(
            uf.get_allocator(), std::allocator_arg, uf.get_allocator()))
    {
    }


    void operator()(T t)
    {
      promise_->set_value(t);
    }

    template <typename Allocator>
    promise_handler(use_future_t<Allocator> uf)
      : promise_(std::allocate_shared<std::promise<void> >(
            uf.get_allocator(), std::allocator_arg, uf.get_allocator()))
    {
    }


    void operator()()
    {
      promise_->set_value();
    }

  template <typename Function, typename T>
  void asio_handler_invoke(Function f, promise_handler<T>* h)
  {
    std::shared_ptr<std::promise<T> > p(h->promise_);
    try
    {
      f();
    }
    catch (...)
    {
      p->set_exception(std::current_exception());
    }
  }

  explicit async_result(detail::promise_handler<T>& h)
  {
    value_ = h.promise_->get_future();
  }

  type get() { return std::move(value_); }


template <typename SyncRandomAccessReadDevice, typename MutableBufferSequence,
    typename CompletionCondition>
std::size_t read_at(SyncRandomAccessReadDevice& d,
    uint64_t offset, const MutableBufferSequence& buffers,
    CompletionCondition completion_condition, boost::system::error_code& ec)
{
  ec = boost::system::error_code();
  boost::asio::detail::consuming_buffers<
    mutable_buffer, MutableBufferSequence> tmp(buffers);
  std::size_t total_transferred = 0;
  tmp.prepare(detail::adapt_completion_condition_result(
        completion_condition(ec, total_transferred)));
  while (tmp.begin() != tmp.end())
  {
    std::size_t bytes_transferred = d.read_some_at(
        offset + total_transferred, tmp, ec);
    tmp.consume(bytes_transferred);
    total_transferred += bytes_transferred;
    tmp.prepare(detail::adapt_completion_condition_result(
          completion_condition(ec, total_transferred)));
  }
  return total_transferred;
}

    read_at_op(AsyncRandomAccessReadDevice& device,
        uint64_t offset, const MutableBufferSequence& buffers,
        CompletionCondition completion_condition, ReadHandler& handler)
      : detail::base_from_completion_cond<
          CompletionCondition>(completion_condition),
        device_(device),
        offset_(offset),
        buffers_(buffers),
        start_(0),
        total_transferred_(0),
        handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(handler))
    {
    }


    void operator()(const boost::system::error_code& ec,
        std::size_t bytes_transferred, int start = 0)
    {
      switch (start_ = start)
      {
        case 1:
        buffers_.prepare(this->check_for_completion(ec, total_transferred_));
        for (;;)
        {
          device_.async_read_some_at(offset_ + total_transferred_,
              buffers_, BOOST_ASIO_MOVE_CAST(read_at_op)(*this));
          return; default:
          total_transferred_ += bytes_transferred;
          buffers_.consume(bytes_transferred);
          buffers_.prepare(this->check_for_completion(ec, total_transferred_));
          if ((!ec && bytes_transferred == 0)
              || buffers_.begin() == buffers_.end())
            break;
        }

        handler_(ec, static_cast<const std::size_t&>(total_transferred_));
      }
    }


  template <typename AsyncRandomAccessReadDevice,
      typename MutableBufferSequence, typename CompletionCondition,
      typename ReadHandler>
  inline void* asio_handler_allocate(std::size_t size,
      read_at_op<AsyncRandomAccessReadDevice, MutableBufferSequence,
        CompletionCondition, ReadHandler>* this_handler)
  {
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
  }


  template <typename AsyncRandomAccessReadDevice,
      typename MutableBufferSequence, typename CompletionCondition,
      typename ReadHandler>
  inline void asio_handler_deallocate(void* pointer, std::size_t size,
      read_at_op<AsyncRandomAccessReadDevice, MutableBufferSequence,
        CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
  }


  template <typename AsyncRandomAccessReadDevice,
      typename MutableBufferSequence, typename CompletionCondition,
      typename ReadHandler>
  inline bool asio_handler_is_continuation(
      read_at_op<AsyncRandomAccessReadDevice, MutableBufferSequence,
        CompletionCondition, ReadHandler>* this_handler)
  {
    return this_handler->start_ == 0 ? true
      : boost_asio_handler_cont_helpers::is_continuation(
          this_handler->handler_);
  }


  template <typename Function, typename AsyncRandomAccessReadDevice,
      typename MutableBufferSequence, typename CompletionCondition,
      typename ReadHandler>
  inline void asio_handler_invoke(Function& function,
      read_at_op<AsyncRandomAccessReadDevice, MutableBufferSequence,
        CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }


  template <typename Function, typename AsyncRandomAccessReadDevice,
      typename MutableBufferSequence, typename CompletionCondition,
      typename ReadHandler>
  inline void asio_handler_invoke(const Function& function,
      read_at_op<AsyncRandomAccessReadDevice, MutableBufferSequence,
        CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }


  template <typename AsyncRandomAccessReadDevice,
      typename MutableBufferSequence, typename CompletionCondition,
      typename ReadHandler>
  inline read_at_op<AsyncRandomAccessReadDevice,
      MutableBufferSequence, CompletionCondition, ReadHandler>
  make_read_at_op(AsyncRandomAccessReadDevice& d,
      uint64_t offset, const MutableBufferSequence& buffers,
      CompletionCondition completion_condition, ReadHandler handler)
  {
    return read_at_op<AsyncRandomAccessReadDevice,
      MutableBufferSequence, CompletionCondition, ReadHandler>(
        d, offset, buffers, completion_condition, handler);
  }

async_read_at(AsyncRandomAccessReadDevice& d,
    uint64_t offset, const MutableBufferSequence& buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler)
{
  // If you get an error on the following line it means that your handler does
  // not meet the documented type requirements for a ReadHandler.
  BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;

  detail::async_result_init<
    ReadHandler, void (boost::system::error_code, std::size_t)> init(
      BOOST_ASIO_MOVE_CAST(ReadHandler)(handler));

  detail::read_at_op<AsyncRandomAccessReadDevice, MutableBufferSequence,
    CompletionCondition, BOOST_ASIO_HANDLER_TYPE(ReadHandler,
      void (boost::system::error_code, std::size_t))>(
        d, offset, buffers, completion_condition, init.handler)(
          boost::system::error_code(), 0, 1);

  return init.result.get();
}

    read_at_streambuf_op(AsyncRandomAccessReadDevice& device,
        uint64_t offset, basic_streambuf<Allocator>& streambuf,
        CompletionCondition completion_condition, ReadHandler& handler)
      : detail::base_from_completion_cond<
          CompletionCondition>(completion_condition),
        device_(device),
        offset_(offset),
        streambuf_(streambuf),
        start_(0),
        total_transferred_(0),
        handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(handler))
    {
    }


    void operator()(const boost::system::error_code& ec,
        std::size_t bytes_transferred, int start = 0)
    {
      std::size_t max_size, bytes_available;
      switch (start_ = start)
      {
        case 1:
        max_size = this->check_for_completion(ec, total_transferred_);
        bytes_available = read_size_helper(streambuf_, max_size);
        for (;;)
        {
          device_.async_read_some_at(offset_ + total_transferred_,
              streambuf_.prepare(bytes_available),
              BOOST_ASIO_MOVE_CAST(read_at_streambuf_op)(*this));
          return; default:
          total_transferred_ += bytes_transferred;
          streambuf_.commit(bytes_transferred);
          max_size = this->check_for_completion(ec, total_transferred_);
          bytes_available = read_size_helper(streambuf_, max_size);
          if ((!ec && bytes_transferred == 0) || bytes_available == 0)
            break;
        }

        handler_(ec, static_cast<const std::size_t&>(total_transferred_));
      }
    }


  template <typename AsyncRandomAccessReadDevice, typename Allocator,
      typename CompletionCondition, typename ReadHandler>
  inline bool asio_handler_is_continuation(
      read_at_streambuf_op<AsyncRandomAccessReadDevice, Allocator,
        CompletionCondition, ReadHandler>* this_handler)
  {
    return this_handler->start_ == 0 ? true
      : boost_asio_handler_cont_helpers::is_continuation(
          this_handler->handler_);
  }


  template <typename Function, typename AsyncRandomAccessReadDevice,
      typename Allocator, typename CompletionCondition, typename ReadHandler>
  inline void asio_handler_invoke(Function& function,
      read_at_streambuf_op<AsyncRandomAccessReadDevice, Allocator,
        CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }


  template <typename Function, typename AsyncRandomAccessReadDevice,
      typename Allocator, typename CompletionCondition, typename ReadHandler>
  inline void asio_handler_invoke(const Function& function,
      read_at_streambuf_op<AsyncRandomAccessReadDevice, Allocator,
        CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

    coro_handler(basic_yield_context<Handler> ctx)
      : coro_(ctx.coro_.lock()),
        ca_(ctx.ca_),
        handler_(ctx.handler_),
        ec_(ctx.ec_),
        value_(0)
    {
    }


    void operator()(T value)
    {
      *ec_ = boost::system::error_code();
      *value_ = value;
      (*coro_)();
    }

    coro_handler(basic_yield_context<Handler> ctx)
      : coro_(ctx.coro_.lock()),
        ca_(ctx.ca_),
        handler_(ctx.handler_),
        ec_(ctx.ec_)
    {
    }


    void operator()()
    {
      *ec_ = boost::system::error_code();
      (*coro_)();
    }


  template <typename Handler, typename T>
  inline void* asio_handler_allocate(std::size_t size,
      coro_handler<Handler, T>* this_handler)
  {
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
  }


  template <typename Handler, typename T>
  inline void asio_handler_deallocate(void* pointer, std::size_t size,
      coro_handler<Handler, T>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
  }


  template <typename Handler, typename T>
  inline bool asio_handler_is_continuation(coro_handler<Handler, T>*)
  {
    return true;
  }


  template <typename Function, typename Handler, typename T>
  inline void asio_handler_invoke(Function& function,
      coro_handler<Handler, T>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }


  template <typename Function, typename Handler, typename T>
  inline void asio_handler_invoke(const Function& function,
      coro_handler<Handler, T>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }


  explicit async_result(detail::coro_handler<Handler, T>& h)
    : ca_(h.ca_)
  {
    out_ec_ = h.ec_;
    if (!out_ec_) h.ec_ = &ec_;
    h.value_ = &value_;
  }


  type get()
  {
    ca_();
    if (!out_ec_ && ec_) throw boost::system::system_error(ec_);
    return value_;
  }

    spawn_data(BOOST_ASIO_MOVE_ARG(Handler) handler,
        bool call_handler, BOOST_ASIO_MOVE_ARG(Function) function)
      : handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
        call_handler_(call_handler),
        function_(BOOST_ASIO_MOVE_CAST(Function)(function))
    {
    }

    void operator()(typename basic_yield_context<Handler>::caller_type& ca)
    {
      shared_ptr<spawn_data<Handler, Function> > data(data_);
      ca(); // Yield until coroutine pointer has been initialised.
      const basic_yield_context<Handler> yield(
          data->coro_, ca, data->handler_);
      (data->function_)(yield);
      if (data->call_handler_)
        (data->handler_)();
    }

    void operator()()
    {
      typedef typename basic_yield_context<Handler>::callee_type callee_type;
      coro_entry_point<Handler, Function> entry_point = { data_ };
      shared_ptr<callee_type> coro(new callee_type(entry_point, attributes_));
      data_->coro_ = coro;
      (*coro)();
    }


  inline void default_spawn_handler() {}

  explicit rfc2818_verification(const std::string& host)
    : host_(host)
  {
  }


inline boost::system::error_code make_error_code(ssl_errors e)
{
  return boost::system::error_code(
      static_cast<int>(e), get_ssl_category());
}

  explicit verify_context(native_handle_type handle)
    : handle_(handle)
  {
  }

  native_handle_type native_handle()
  {
    return handle_;
  }

  template <typename Arg>
  stream(Arg& arg, context& ctx)
    : next_layer_(arg),
      core_(ctx.native_handle(), next_layer_.lowest_layer().get_io_service())
  {
    backwards_compatible_impl_.ssl = core_.engine_.native_handle();
  }

  ~stream()
  {
  }

  boost::asio::io_service& get_io_service()
  {
    return next_layer_.lowest_layer().get_io_service();
  }

  native_handle_type native_handle()
  {
    return core_.engine_.native_handle();
  }

  impl_type impl()
  {
    return &backwards_compatible_impl_;
  }

  const next_layer_type& next_layer() const
  {
    return next_layer_;
  }

  lowest_layer_type& lowest_layer()
  {
    return next_layer_.lowest_layer();
  }

  const lowest_layer_type& lowest_layer() const
  {
    return next_layer_.lowest_layer();
  }

  void set_verify_mode(verify_mode v)
  {
    boost::system::error_code ec;
    set_verify_mode(v, ec);
    boost::asio::detail::throw_error(ec, "set_verify_mode");
  }

  void set_verify_depth(int depth)
  {
    boost::system::error_code ec;
    set_verify_depth(depth, ec);
    boost::asio::detail::throw_error(ec, "set_verify_depth");
  }

  template <typename VerifyCallback>
  void set_verify_callback(VerifyCallback callback)
  {
    boost::system::error_code ec;
    this->set_verify_callback(callback, ec);
    boost::asio::detail::throw_error(ec, "set_verify_callback");
  }

  void handshake(handshake_type type)
  {
    boost::system::error_code ec;
    handshake(type, ec);
    boost::asio::detail::throw_error(ec, "handshake");
  }

  ~context_base()
  {
  }

  ~stream_base()
  {
  }


template <typename Stream, typename Operation>
std::size_t io(Stream& next_layer, stream_core& core,
    const Operation& op, boost::system::error_code& ec)
{
  std::size_t bytes_transferred = 0;
  do switch (op(core.engine_, ec, bytes_transferred))
  {
  case engine::want_input_and_retry:

    // If the input buffer is empty then we need to read some more data from
    // the underlying transport.
    if (boost::asio::buffer_size(core.input_) == 0)
      core.input_ = boost::asio::buffer(core.input_buffer_,
          next_layer.read_some(core.input_buffer_, ec));

    // Pass the new input data to the engine.
    core.input_ = core.engine_.put_input(core.input_);

    // Try the operation again.
    continue;

  case engine::want_output_and_retry:

    // Get output data from the engine and write it to the underlying
    // transport.
    boost::asio::write(next_layer,
        core.engine_.get_output(core.output_buffer_), ec);

    // Try the operation again.
    continue;

  case engine::want_output:

    // Get output data from the engine and write it to the underlying
    // transport.
    boost::asio::write(next_layer,
        core.engine_.get_output(core.output_buffer_), ec);

    // Operation is complete. Return result to caller.
    core.engine_.map_error_code(ec);
    return bytes_transferred;

  default:

    // Operation is complete. Return result to caller.
    core.engine_.map_error_code(ec);
    return bytes_transferred;

  } while (!ec);

  // Operation failed. Return result to caller.
  core.engine_.map_error_code(ec);
  return 0;
}

  io_op(Stream& next_layer, stream_core& core,
      const Operation& op, Handler& handler)
    : next_layer_(next_layer),
      core_(core),
      op_(op),
      start_(0),
      bytes_transferred_(0),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler))
  {
  }


  void operator()(boost::system::error_code ec,
      std::size_t bytes_transferred = ~std::size_t(0), int start = 0)
  {
    switch (start_ = start)
    {
    case 1: // Called after at least one async operation.
      do
      {
        switch (want_ = op_(core_.engine_, ec_, bytes_transferred_))
        {
        case engine::want_input_and_retry:

          // If the input buffer already has data in it we can pass it to the
          // engine and then retry the operation immediately.
          if (boost::asio::buffer_size(core_.input_) != 0)
          {
            core_.input_ = core_.engine_.put_input(core_.input_);
            continue;
          }

          // The engine wants more data to be read from input. However, we
          // cannot allow more than one read operation at a time on the
          // underlying transport. The pending_read_ timer's expiry is set to
          // pos_infin if a read is in progress, and neg_infin otherwise.
          if (core_.pending_read_.expires_at() == core_.neg_infin())
          {
            // Prevent other read operations from being started.
            core_.pending_read_.expires_at(core_.pos_infin());

            // Start reading some data from the underlying transport.
            next_layer_.async_read_some(
                boost::asio::buffer(core_.input_buffer_),
                BOOST_ASIO_MOVE_CAST(io_op)(*this));
          }
          else
          {
            // Wait until the current read operation completes.
            core_.pending_read_.async_wait(BOOST_ASIO_MOVE_CAST(io_op)(*this));
          }

          // Yield control until asynchronous operation completes. Control
          // resumes at the "default:" label below.
          return;

        case engine::want_output_and_retry:
        case engine::want_output:

          // The engine wants some data to be written to the output. However, we
          // cannot allow more than one write operation at a time on the
          // underlying transport. The pending_write_ timer's expiry is set to
          // pos_infin if a write is in progress, and neg_infin otherwise.
          if (core_.pending_write_.expires_at() == core_.neg_infin())
          {
            // Prevent other write operations from being started.
            core_.pending_write_.expires_at(core_.pos_infin());

            // Start writing all the data to the underlying transport.
            boost::asio::async_write(next_layer_,
                core_.engine_.get_output(core_.output_buffer_),
                BOOST_ASIO_MOVE_CAST(io_op)(*this));
          }
          else
          {
            // Wait until the current write operation completes.
            core_.pending_write_.async_wait(BOOST_ASIO_MOVE_CAST(io_op)(*this));
          }

          // Yield control until asynchronous operation completes. Control
          // resumes at the "default:" label below.
          return;

        default:

          // The SSL operation is done and we can invoke the handler, but we
          // have to keep in mind that this function might be being called from
          // the async operation's initiating function. In this case we're not
          // allowed to call the handler directly. Instead, issue a zero-sized
          // read so the handler runs "as-if" posted using io_service::post().
          if (start)
          {
            next_layer_.async_read_some(
                boost::asio::buffer(core_.input_buffer_, 0),
                BOOST_ASIO_MOVE_CAST(io_op)(*this));

            // Yield control until asynchronous operation completes. Control
            // resumes at the "default:" label below.
            return;
          }
          else
          {
            // Continue on to run handler directly.
            break;
          }
        }

        default:
        if (bytes_transferred != ~std::size_t(0) && !ec_)
          ec_ = ec;

        switch (want_)
        {
        case engine::want_input_and_retry:

          // Add received data to the engine's input.
          core_.input_ = boost::asio::buffer(
              core_.input_buffer_, bytes_transferred);
          core_.input_ = core_.engine_.put_input(core_.input_);

          // Release any waiting read operations.
          core_.pending_read_.expires_at(core_.neg_infin());

          // Try the operation again.
          continue;

        case engine::want_output_and_retry:

          // Release any waiting write operations.
          core_.pending_write_.expires_at(core_.neg_infin());

          // Try the operation again.
          continue;

        case engine::want_output:

          // Release any waiting write operations.
          core_.pending_write_.expires_at(core_.neg_infin());

          // Fall through to call handler.

        default:

          // Pass the result to the handler.
          op_.call_handler(handler_,
              core_.engine_.map_error_code(ec_),
              ec_ ? 0 : bytes_transferred_);

          // Our work here is done.
          return;
        }
      } while (!ec_);

      // Operation failed. Pass the result to the handler.
      op_.call_handler(handler_, core_.engine_.map_error_code(ec_), 0);
    }
  }


template <typename Stream, typename Operation,  typename Handler>
inline void* asio_handler_allocate(std::size_t size,
    io_op<Stream, Operation, Handler>* this_handler)
{
  return boost_asio_handler_alloc_helpers::allocate(
      size, this_handler->handler_);
}


template <typename Stream, typename Operation, typename Handler>
inline void asio_handler_deallocate(void* pointer, std::size_t size,
    io_op<Stream, Operation, Handler>* this_handler)
{
  boost_asio_handler_alloc_helpers::deallocate(
      pointer, size, this_handler->handler_);
}


template <typename Stream, typename Operation, typename Handler>
inline bool asio_handler_is_continuation(
    io_op<Stream, Operation, Handler>* this_handler)
{
  return this_handler->start_ == 0 ? true
    : boost_asio_handler_cont_helpers::is_continuation(this_handler->handler_);
}


template <typename Function, typename Stream,
    typename Operation, typename Handler>
inline void asio_handler_invoke(Function& function,
    io_op<Stream, Operation, Handler>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
}


template <typename Function, typename Stream,
    typename Operation, typename Handler>
inline void asio_handler_invoke(const Function& function,
    io_op<Stream, Operation, Handler>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
}


template <typename Stream, typename Operation, typename Handler>
inline void async_io(Stream& next_layer, stream_core& core,
    const Operation& op, Handler& handler)
{
  io_op<Stream, Operation, Handler>(
    next_layer, core, op, handler)(
      boost::system::error_code(), 0, 1);
}

  read_op(const MutableBufferSequence& buffers)
    : buffers_(buffers)
  {
  }


  engine::want operator()(engine& eng,
      boost::system::error_code& ec,
      std::size_t& bytes_transferred) const
  {
    boost::asio::mutable_buffer buffer =
      boost::asio::detail::buffer_sequence_adapter<boost::asio::mutable_buffer,
        MutableBufferSequence>::first(buffers_);

    return eng.read(buffer, ec, bytes_transferred);
  }


  template <typename Handler>
  void call_handler(Handler& handler,
      const boost::system::error_code& ec,
      const std::size_t& bytes_transferred) const
  {
    handler(ec, bytes_transferred);
  }


  stream_core(SSL_CTX* context, boost::asio::io_service& io_service)
    : engine_(context),
      pending_read_(io_service),
      pending_write_(io_service),
      output_buffer_space_(max_tls_record_size),
      output_buffer_(boost::asio::buffer(output_buffer_space_)),
      input_buffer_space_(max_tls_record_size),
      input_buffer_(boost::asio::buffer(input_buffer_space_))
  {
    pending_read_.expires_at(neg_infin());
    pending_write_.expires_at(neg_infin());
  }


  ~stream_core()
  {
  }

  static boost::asio::steady_timer::time_point neg_infin()
  {
    return boost::asio::steady_timer::time_point::min();
  }

  static boost::asio::steady_timer::time_point pos_infin()
  {
    return boost::asio::steady_timer::time_point::max();
  }

  handshake_op(stream_base::handshake_type type)
    : type_(type)
  {
  }


  engine::want operator()(engine& eng,
      boost::system::error_code& ec,
      std::size_t& bytes_transferred) const
  {
    bytes_transferred = 0;
    return eng.handshake(type_, ec);
  }


  template <typename Handler>
  void call_handler(Handler& handler,
      const boost::system::error_code& ec,
      const std::size_t&) const
  {
    handler(ec);
  }

  virtual ~verify_callback_base()
  {
  }

  explicit verify_callback(VerifyCallback callback)
    : callback_(callback)
  {
  }


  virtual bool call(bool preverified, verify_context& ctx)
  {
    return callback_(preverified, ctx);
  }

  openssl_init()
    : ref_(instance())
  {
    using namespace std; // For memmove.

    // Ensure openssl_init::instance_ is linked in.
    openssl_init* tmp = &instance_;
    memmove(&tmp, &tmp, sizeof(openssl_init*));
  }

  ~openssl_init()
  {
  }

  engine::want operator()(engine& eng,
      boost::system::error_code& ec,
      std::size_t& bytes_transferred) const
  {
    bytes_transferred = 0;
    return eng.shutdown(ec);
  }


  template <typename Handler>
  void call_handler(Handler& handler,
      const boost::system::error_code& ec,
      const std::size_t&) const
  {
    handler(ec);
  }

  write_op(const ConstBufferSequence& buffers)
    : buffers_(buffers)
  {
  }


  engine::want operator()(engine& eng,
      boost::system::error_code& ec,
      std::size_t& bytes_transferred) const
  {
    boost::asio::const_buffer buffer =
      boost::asio::detail::buffer_sequence_adapter<boost::asio::const_buffer,
        ConstBufferSequence>::first(buffers_);

    return eng.write(buffer, ec, bytes_transferred);
  }


  template <typename Handler>
  void call_handler(Handler& handler,
      const boost::system::error_code& ec,
      const std::size_t& bytes_transferred) const
  {
    handler(ec, bytes_transferred);
  }

  buffered_handshake_op(stream_base::handshake_type type,
      const ConstBufferSequence& buffers)
    : type_(type),
      buffers_(buffers),
      total_buffer_size_(boost::asio::buffer_size(buffers_))
  {
  }


  engine::want operator()(engine& eng,
      boost::system::error_code& ec,
      std::size_t& bytes_transferred) const
  {
    typename ConstBufferSequence::const_iterator iter = buffers_.begin();
    typename ConstBufferSequence::const_iterator end = buffers_.end();
    std::size_t accumulated_size = 0;

    for (;;)
    {
      engine::want want = eng.handshake(type_, ec);
      if (want != engine::want_input_and_retry
          || bytes_transferred == total_buffer_size_)
        return want;

      // Find the next buffer piece to be fed to the engine.
      while (iter != end)
      {
        const_buffer buffer(*iter);

        // Skip over any buffers which have already been consumed by the engine.
        if (bytes_transferred >= accumulated_size + buffer_size(buffer))
        {
          accumulated_size += buffer_size(buffer);
          ++iter;
          continue;
        }

        // The current buffer may have been partially consumed by the engine on
        // a previous iteration. If so, adjust the buffer to point to the
        // unused portion.
        if (bytes_transferred > accumulated_size)
          buffer = buffer + (bytes_transferred - accumulated_size);

        // Pass the buffer to the engine, and update the bytes transferred to
        // reflect the total number of bytes consumed so far.
        bytes_transferred += buffer_size(buffer);
        buffer = eng.put_input(buffer);
        bytes_transferred -= buffer_size(buffer);
        break;
      }
    }
  }


  template <typename Handler>
  void call_handler(Handler& handler,
      const boost::system::error_code& ec,
      const std::size_t& bytes_transferred) const
  {
    handler(ec, bytes_transferred);
  }

  virtual ~password_callback_base()
  {
  }

  explicit password_callback(PasswordCallback callback)
    : callback_(callback)
  {
  }


  virtual std::string call(std::size_t size,
      context_base::password_purpose purpose)
  {
    return callback_(size, purpose);
  }

  explicit context_service(boost::asio::io_service& io_service)
    : boost::asio::detail::service_base<context_service>(io_service),
      service_impl_(boost::asio::use_service<service_impl_type>(io_service))
  {
  }

  impl_type null() const
  {
    return service_impl_.null();
  }

  void create(impl_type& impl, context_base::method m)
  {
    service_impl_.create(impl, m);
  }

  void destroy(impl_type& impl)
  {
    service_impl_.destroy(impl);
  }

  boost::system::error_code set_options(impl_type& impl,
      context_base::options o, boost::system::error_code& ec)
  {
    return service_impl_.set_options(impl, o, ec);
  }

  boost::system::error_code set_verify_mode(impl_type& impl,
      context_base::verify_mode v, boost::system::error_code& ec)
  {
    return service_impl_.set_verify_mode(impl, v, ec);
  }

  boost::system::error_code load_verify_file(impl_type& impl,
      const std::string& filename, boost::system::error_code& ec)
  {
    return service_impl_.load_verify_file(impl, filename, ec);
  }

  boost::system::error_code add_verify_path(impl_type& impl,
      const std::string& path, boost::system::error_code& ec)
  {
    return service_impl_.add_verify_path(impl, path, ec);
  }

  boost::system::error_code use_certificate_file(impl_type& impl,
      const std::string& filename, context_base::file_format format,
      boost::system::error_code& ec)
  {
    return service_impl_.use_certificate_file(impl, filename, format, ec);
  }

  boost::system::error_code use_certificate_chain_file(impl_type& impl,
      const std::string& filename, boost::system::error_code& ec)
  {
    return service_impl_.use_certificate_chain_file(impl, filename, ec);
  }

  boost::system::error_code use_private_key_file(impl_type& impl,
      const std::string& filename, context_base::file_format format,
      boost::system::error_code& ec)
  {
    return service_impl_.use_private_key_file(impl, filename, format, ec);
  }

  boost::system::error_code use_rsa_private_key_file(impl_type& impl,
      const std::string& filename, context_base::file_format format,
      boost::system::error_code& ec)
  {
    return service_impl_.use_rsa_private_key_file(impl, filename, format, ec);
  }

  boost::system::error_code use_tmp_dh_file(impl_type& impl,
      const std::string& filename, boost::system::error_code& ec)
  {
    return service_impl_.use_tmp_dh_file(impl, filename, ec);
  }

  template <typename PasswordCallback>
  boost::system::error_code set_password_callback(impl_type& impl,
      PasswordCallback callback, boost::system::error_code& ec)
  {
    return service_impl_.set_password_callback(impl, callback, ec);
  }

  void shutdown_service()
  {
  }

  basic_context(boost::asio::io_service& io_service, method m)
    : service_(boost::asio::use_service<Service>(io_service)),
      impl_(service_.null())
  {
    service_.create(impl_, m);
  }

  ~basic_context()
  {
    service_.destroy(impl_);
  }

  impl_type impl()
  {
    return impl_;
  }

  void set_options(options o)
  {
    boost::system::error_code ec;
    service_.set_options(impl_, o, ec);
    boost::asio::detail::throw_error(ec);
  }

  void set_verify_mode(verify_mode v)
  {
    boost::system::error_code ec;
    service_.set_verify_mode(impl_, v, ec);
    boost::asio::detail::throw_error(ec);
  }

  void load_verify_file(const std::string& filename)
  {
    boost::system::error_code ec;
    service_.load_verify_file(impl_, filename, ec);
    boost::asio::detail::throw_error(ec);
  }

  void add_verify_path(const std::string& path)
  {
    boost::system::error_code ec;
    service_.add_verify_path(impl_, path, ec);
    boost::asio::detail::throw_error(ec);
  }

  void use_certificate_file(const std::string& filename, file_format format)
  {
    boost::system::error_code ec;
    service_.use_certificate_file(impl_, filename, format, ec);
    boost::asio::detail::throw_error(ec);
  }

  void use_certificate_chain_file(const std::string& filename)
  {
    boost::system::error_code ec;
    service_.use_certificate_chain_file(impl_, filename, ec);
    boost::asio::detail::throw_error(ec);
  }

  void use_private_key_file(const std::string& filename, file_format format)
  {
    boost::system::error_code ec;
    service_.use_private_key_file(impl_, filename, format, ec);
    boost::asio::detail::throw_error(ec);
  }

  void use_rsa_private_key_file(const std::string& filename, file_format format)
  {
    boost::system::error_code ec;
    service_.use_rsa_private_key_file(impl_, filename, format, ec);
    boost::asio::detail::throw_error(ec);
  }

  void use_tmp_dh_file(const std::string& filename)
  {
    boost::system::error_code ec;
    service_.use_tmp_dh_file(impl_, filename, ec);
    boost::asio::detail::throw_error(ec);
  }

  template <typename PasswordCallback>
  void set_password_callback(PasswordCallback callback)
  {
    boost::system::error_code ec;
    service_.set_password_callback(impl_, callback, ec);
    boost::asio::detail::throw_error(ec);
  }

  template <typename Arg, typename Context_Service>
  explicit stream(Arg& arg, basic_context<Context_Service>& context)
    : next_layer_(arg),
      service_(boost::asio::use_service<Service>(next_layer_.get_io_service())),
      impl_(service_.null())
  {
    service_.create(impl_, next_layer_, context);
  }

  ~stream()
  {
    service_.destroy(impl_, next_layer_);
  }

  boost::asio::io_service& get_io_service()
  {
    return next_layer_.get_io_service();
  }

  next_layer_type& next_layer()
  {
    return next_layer_;
  }

  lowest_layer_type& lowest_layer()
  {
    return next_layer_.lowest_layer();
  }

  const lowest_layer_type& lowest_layer() const
  {
    return next_layer_.lowest_layer();
  }

  impl_type impl()
  {
    return impl_;
  }

  void handshake(handshake_type type)
  {
    boost::system::error_code ec;
    service_.handshake(impl_, next_layer_, type, ec);
    boost::asio::detail::throw_error(ec);
  }

  template <typename HandshakeHandler>
  void async_handshake(handshake_type type, HandshakeHandler handler)
  {
    service_.async_handshake(impl_, next_layer_, type, handler);
  }

  void shutdown()
  {
    boost::system::error_code ec;
    service_.shutdown(impl_, next_layer_, ec);
    boost::asio::detail::throw_error(ec);
  }

  template <typename ShutdownHandler>
  void async_shutdown(ShutdownHandler handler)
  {
    service_.async_shutdown(impl_, next_layer_, handler);
  }

  template <typename ConstBufferSequence>
  std::size_t write_some(const ConstBufferSequence& buffers)
  {
    boost::system::error_code ec;
    std::size_t s = service_.write_some(impl_, next_layer_, buffers, ec);
    boost::asio::detail::throw_error(ec);
    return s;
  }

  template <typename ConstBufferSequence, typename WriteHandler>
  void async_write_some(const ConstBufferSequence& buffers,
      WriteHandler handler)
  {
    service_.async_write_some(impl_, next_layer_, buffers, handler);
  }

  template <typename MutableBufferSequence>
  std::size_t read_some(const MutableBufferSequence& buffers)
  {
    boost::system::error_code ec;
    std::size_t s = service_.read_some(impl_, next_layer_, buffers, ec);
    boost::asio::detail::throw_error(ec);
    return s;
  }

  template <typename MutableBufferSequence, typename ReadHandler>
  void async_read_some(const MutableBufferSequence& buffers,
      ReadHandler handler)
  {
    service_.async_read_some(impl_, next_layer_, buffers, handler);
  }

  template <typename MutableBufferSequence>
  std::size_t peek(const MutableBufferSequence& buffers)
  {
    boost::system::error_code ec;
    std::size_t s = service_.peek(impl_, next_layer_, buffers, ec);
    boost::asio::detail::throw_error(ec);
    return s;
  }

  std::size_t in_avail()
  {
    boost::system::error_code ec;
    std::size_t s = service_.in_avail(impl_, next_layer_, ec);
    boost::asio::detail::throw_error(ec);
    return s;
  }

  explicit stream_service(boost::asio::io_service& io_service)
    : boost::asio::detail::service_base<stream_service>(io_service),
      service_impl_(boost::asio::use_service<service_impl_type>(io_service))
  {
  }

  impl_type null() const
  {
    return service_impl_.null();
  }

  template <typename Stream, typename Context_Service>
  void create(impl_type& impl, Stream& next_layer,
      basic_context<Context_Service>& context)
  {
    service_impl_.create(impl, next_layer, context);
  }

  template <typename Stream>
  void destroy(impl_type& impl, Stream& next_layer)
  {
    service_impl_.destroy(impl, next_layer);
  }

  template <typename Stream>
  boost::system::error_code handshake(impl_type& impl, Stream& next_layer,
      stream_base::handshake_type type, boost::system::error_code& ec)
  {
    return service_impl_.handshake(impl, next_layer, type, ec);
  }

  template <typename Stream, typename HandshakeHandler>
  void async_handshake(impl_type& impl, Stream& next_layer,
      stream_base::handshake_type type, HandshakeHandler handler)
  {
    service_impl_.async_handshake(impl, next_layer, type, handler);
  }

  template <typename Stream>
  boost::system::error_code shutdown(impl_type& impl, Stream& next_layer,
      boost::system::error_code& ec)
  {
    return service_impl_.shutdown(impl, next_layer, ec);
  }

  template <typename Stream, typename ShutdownHandler>
  void async_shutdown(impl_type& impl, Stream& next_layer,
      ShutdownHandler handler)
  {
    service_impl_.async_shutdown(impl, next_layer, handler);
  }

  template <typename Stream, typename ConstBufferSequence>
  std::size_t write_some(impl_type& impl, Stream& next_layer,
      const ConstBufferSequence& buffers, boost::system::error_code& ec)
  {
    return service_impl_.write_some(impl, next_layer, buffers, ec);
  }

  template <typename Stream, typename ConstBufferSequence,
      typename WriteHandler>
  void async_write_some(impl_type& impl, Stream& next_layer,
      const ConstBufferSequence& buffers, WriteHandler handler)
  {
    service_impl_.async_write_some(impl, next_layer, buffers, handler);
  }

  template <typename Stream, typename MutableBufferSequence>
  std::size_t read_some(impl_type& impl, Stream& next_layer,
      const MutableBufferSequence& buffers, boost::system::error_code& ec)
  {
    return service_impl_.read_some(impl, next_layer, buffers, ec);
  }

  template <typename Stream, typename MutableBufferSequence,
      typename ReadHandler>
  void async_read_some(impl_type& impl, Stream& next_layer,
      const MutableBufferSequence& buffers, ReadHandler handler)
  {
    service_impl_.async_read_some(impl, next_layer, buffers, handler);
  }

  template <typename Stream, typename MutableBufferSequence>
  std::size_t peek(impl_type& impl, Stream& next_layer,
      const MutableBufferSequence& buffers, boost::system::error_code& ec)
  {
    return service_impl_.peek(impl, next_layer, buffers, ec);
  }

  template <typename Stream>
  std::size_t in_avail(impl_type& impl, Stream& next_layer,
      boost::system::error_code& ec)
  {
    return service_impl_.in_avail(impl, next_layer, ec);
  }

  void shutdown_service()
  {
  }


    base_handler(boost::asio::io_service& io_service)
      : op_(NULL)
      , io_service_(io_service)
      , work_(io_service)
    {}

    
    void do_func(const boost::system::error_code& error, size_t size)
    {
      func_(error, size);
    }

        
    void set_operation(openssl_operation<Stream>* op) { op_ = op; }

    void set_func(func_t func) { func_ = func; }


    ~base_handler()
    {
      delete op_;
    }

    io_handler(Handler handler, boost::asio::io_service& io_service)
      : base_handler<Stream>(io_service)
      , handler_(handler)
    {
      this->set_func(boost::bind(
        &io_handler<Stream, Handler>::handler_impl, 
        this, boost::arg<1>(), boost::arg<2>() ));
    }

    void handler_impl(const boost::system::error_code& error, size_t size)
    {
      std::auto_ptr<io_handler<Stream, Handler> > this_ptr(this);
      handler_(error, size);
    }

    handshake_handler(Handler handler, boost::asio::io_service& io_service)
      : base_handler<Stream>(io_service)
      , handler_(handler)
    {
      this->set_func(boost::bind(
        &handshake_handler<Stream, Handler>::handler_impl, 
        this, boost::arg<1>(), boost::arg<2>() ));
    }

    void handler_impl(const boost::system::error_code& error, size_t)
    {
      std::auto_ptr<handshake_handler<Stream, Handler> > this_ptr(this);
      handler_(error);
    }

    shutdown_handler(Handler handler, boost::asio::io_service& io_service)
      : base_handler<Stream>(io_service),
        handler_(handler)
    { 
      this->set_func(boost::bind(
        &shutdown_handler<Stream, Handler>::handler_impl, 
        this, boost::arg<1>(), boost::arg<2>() ));
    }

    void handler_impl(const boost::system::error_code& error, size_t)
    {
      std::auto_ptr<shutdown_handler<Stream, Handler> > this_ptr(this);
      handler_(error);
    }

  explicit openssl_stream_service(boost::asio::io_service& io_service)
    : boost::asio::detail::service_base<openssl_stream_service>(io_service),
      strand_(io_service)
  {
  }

  void shutdown_service()
  {
  }

  impl_type null() const
  {
    return 0;
  }

  template <typename Stream, typename Context_Service>
  void create(impl_type& impl, Stream& /*next_layer*/,
      basic_context<Context_Service>& context)
  {
    impl = new impl_struct;
    impl->ssl = ::SSL_new(context.impl());
    ::SSL_set_mode(impl->ssl, SSL_MODE_ENABLE_PARTIAL_WRITE);
    ::SSL_set_mode(impl->ssl, SSL_MODE_ACCEPT_MOVING_WRITE_BUFFER);
    ::BIO* int_bio = 0;
    impl->ext_bio = 0;
    ::BIO_new_bio_pair(&int_bio, 8192, &impl->ext_bio, 8192);
    ::SSL_set_bio(impl->ssl, int_bio, int_bio);
  }

  template <typename Stream>
  void destroy(impl_type& impl, Stream& /*next_layer*/)
  {
    if (impl != 0)
    {
      ::BIO_free(impl->ext_bio);
      ::SSL_free(impl->ssl);
      delete impl;
      impl = 0;
    }
  }

  template <typename Stream>
  boost::system::error_code handshake(impl_type& impl, Stream& next_layer,
      stream_base::handshake_type type, boost::system::error_code& ec)
  {
    try
    {
      openssl_operation<Stream> op(
        type == stream_base::client ?
          &ssl_wrap<mutex_type>::SSL_connect:
          &ssl_wrap<mutex_type>::SSL_accept,
        next_layer,
        impl->recv_buf,
        impl->ssl,
        impl->ext_bio);
      op.start();
    }
    catch (boost::system::system_error& e)
    {
      ec = e.code();
      return ec;
    }

    ec = boost::system::error_code();
    return ec;
  }

  template <typename Stream, typename Handler>
  void async_handshake(impl_type& impl, Stream& next_layer,
      stream_base::handshake_type type, Handler handler)
  {
    typedef handshake_handler<Stream, Handler> connect_handler;

    connect_handler* local_handler = 
      new connect_handler(handler, get_io_service());

    openssl_operation<Stream>* op = new openssl_operation<Stream>
    (
      type == stream_base::client ?
        &ssl_wrap<mutex_type>::SSL_connect:
        &ssl_wrap<mutex_type>::SSL_accept,
      next_layer,
      impl->recv_buf,
      impl->ssl,
      impl->ext_bio,
      boost::bind
      (
        &base_handler<Stream>::do_func, 
        local_handler,
        boost::arg<1>(),
        boost::arg<2>()
      ),
      strand_
    );
    local_handler->set_operation(op);

    strand_.post(boost::bind(&openssl_operation<Stream>::start, op));
  }

  template <typename Stream>
  boost::system::error_code shutdown(impl_type& impl, Stream& next_layer,
      boost::system::error_code& ec)
  {
    try
    {
      openssl_operation<Stream> op(
        &ssl_wrap<mutex_type>::SSL_shutdown,
        next_layer,
        impl->recv_buf,
        impl->ssl,
        impl->ext_bio);
      op.start();
    }
    catch (boost::system::system_error& e)
    {
      ec = e.code();
      return ec;
    }

    ec = boost::system::error_code();
    return ec;
  }

  template <typename Stream, typename Handler>
  void async_shutdown(impl_type& impl, Stream& next_layer, Handler handler)
  {
    typedef shutdown_handler<Stream, Handler> disconnect_handler;

    disconnect_handler* local_handler = 
      new disconnect_handler(handler, get_io_service());

    openssl_operation<Stream>* op = new openssl_operation<Stream>
    (
      &ssl_wrap<mutex_type>::SSL_shutdown,
      next_layer,
      impl->recv_buf,
      impl->ssl,
      impl->ext_bio,
      boost::bind
      (
        &base_handler<Stream>::do_func, 
        local_handler, 
        boost::arg<1>(),
        boost::arg<2>()
      ),
      strand_
    );
    local_handler->set_operation(op);

    strand_.post(boost::bind(&openssl_operation<Stream>::start, op));        
  }

  template <typename Stream, typename Const_Buffers>
  std::size_t write_some(impl_type& impl, Stream& next_layer,
      const Const_Buffers& buffers, boost::system::error_code& ec)
  {
    size_t bytes_transferred = 0;
    try
    {
      boost::asio::const_buffer buffer =
        boost::asio::detail::buffer_sequence_adapter<
          boost::asio::const_buffer, Const_Buffers>::first(buffers);

      std::size_t buffer_size = boost::asio::buffer_size(buffer);
      if (buffer_size > max_buffer_size)
        buffer_size = max_buffer_size;
      else if (buffer_size == 0)
      {
        ec = boost::system::error_code();
        return 0;
      }

      boost::function<int (SSL*)> send_func =
        boost::bind(boost::type<int>(), &::SSL_write, boost::arg<1>(),  
            boost::asio::buffer_cast<const void*>(buffer),
            static_cast<int>(buffer_size));
      openssl_operation<Stream> op(
        send_func,
        next_layer,
        impl->recv_buf,
        impl->ssl,
        impl->ext_bio
      );
      bytes_transferred = static_cast<size_t>(op.start());
    }
    catch (boost::system::system_error& e)
    {
      ec = e.code();
      return 0;
    }

    ec = boost::system::error_code();
    return bytes_transferred;
  }

  template <typename Stream, typename Const_Buffers, typename Handler>
  void async_write_some(impl_type& impl, Stream& next_layer,
      const Const_Buffers& buffers, Handler handler)
  {
    typedef io_handler<Stream, Handler> send_handler;

    boost::asio::const_buffer buffer =
      boost::asio::detail::buffer_sequence_adapter<
        boost::asio::const_buffer, Const_Buffers>::first(buffers);

    std::size_t buffer_size = boost::asio::buffer_size(buffer);
    if (buffer_size > max_buffer_size)
      buffer_size = max_buffer_size;
    else if (buffer_size == 0)
    {
      get_io_service().post(boost::asio::detail::bind_handler(
            handler, boost::system::error_code(), 0));
      return;
    }

    send_handler* local_handler = new send_handler(handler, get_io_service());

    boost::function<int (SSL*)> send_func =
      boost::bind(boost::type<int>(), &::SSL_write, boost::arg<1>(),
          boost::asio::buffer_cast<const void*>(buffer),
          static_cast<int>(buffer_size));

    openssl_operation<Stream>* op = new openssl_operation<Stream>
    (
      send_func,
      next_layer,
      impl->recv_buf,
      impl->ssl,
      impl->ext_bio,
      boost::bind
      (
        &base_handler<Stream>::do_func, 
        local_handler, 
        boost::arg<1>(),
        boost::arg<2>()
      ),
      strand_
    );
    local_handler->set_operation(op);

    strand_.post(boost::bind(&openssl_operation<Stream>::start, op));        
  }

  template <typename Stream, typename Mutable_Buffers>
  std::size_t read_some(impl_type& impl, Stream& next_layer,
      const Mutable_Buffers& buffers, boost::system::error_code& ec)
  {
    size_t bytes_transferred = 0;
    try
    {
      boost::asio::mutable_buffer buffer =
        boost::asio::detail::buffer_sequence_adapter<
          boost::asio::mutable_buffer, Mutable_Buffers>::first(buffers);

      std::size_t buffer_size = boost::asio::buffer_size(buffer);
      if (buffer_size > max_buffer_size)
        buffer_size = max_buffer_size;
      else if (buffer_size == 0)
      {
        ec = boost::system::error_code();
        return 0;
      }

      boost::function<int (SSL*)> recv_func =
        boost::bind(boost::type<int>(), &::SSL_read, boost::arg<1>(),
            boost::asio::buffer_cast<void*>(buffer),
            static_cast<int>(buffer_size));
      openssl_operation<Stream> op(recv_func,
        next_layer,
        impl->recv_buf,
        impl->ssl,
        impl->ext_bio
      );

      bytes_transferred = static_cast<size_t>(op.start());
    }
    catch (boost::system::system_error& e)
    {
      ec = e.code();
      return 0;
    }

    ec = boost::system::error_code();
    return bytes_transferred;
  }

  template <typename Stream, typename Mutable_Buffers, typename Handler>
  void async_read_some(impl_type& impl, Stream& next_layer,
      const Mutable_Buffers& buffers, Handler handler)
  {
    typedef io_handler<Stream, Handler> recv_handler;

    boost::asio::mutable_buffer buffer =
      boost::asio::detail::buffer_sequence_adapter<
        boost::asio::mutable_buffer, Mutable_Buffers>::first(buffers);

    std::size_t buffer_size = boost::asio::buffer_size(buffer);
    if (buffer_size > max_buffer_size)
      buffer_size = max_buffer_size;
    else if (buffer_size == 0)
    {
      get_io_service().post(boost::asio::detail::bind_handler(
            handler, boost::system::error_code(), 0));
      return;
    }

    recv_handler* local_handler = new recv_handler(handler, get_io_service());

    boost::function<int (SSL*)> recv_func =
      boost::bind(boost::type<int>(), &::SSL_read, boost::arg<1>(),
          boost::asio::buffer_cast<void*>(buffer),
          static_cast<int>(buffer_size));

    openssl_operation<Stream>* op = new openssl_operation<Stream>
    (
      recv_func,
      next_layer,
      impl->recv_buf,
      impl->ssl,
      impl->ext_bio,
      boost::bind
      (
        &base_handler<Stream>::do_func, 
        local_handler, 
        boost::arg<1>(),
        boost::arg<2>()
      ),
      strand_
    );
    local_handler->set_operation(op);

    strand_.post(boost::bind(&openssl_operation<Stream>::start, op));        
  }

  template <typename Stream, typename Mutable_Buffers>
  std::size_t peek(impl_type& /*impl*/, Stream& /*next_layer*/,
      const Mutable_Buffers& /*buffers*/, boost::system::error_code& ec)
  {
    ec = boost::system::error_code();
    return 0;
  }

  template <typename Stream>
  std::size_t in_avail(impl_type& /*impl*/, Stream& /*next_layer*/,
      boost::system::error_code& ec)
  {
    ec = boost::system::error_code();
    return 0;
  }


    static int SSL_accept(SSL *ssl)
    {
      typename Mutex::scoped_lock lock(ssl_mutex_);
      return ::SSL_accept(ssl);
    }

  
    static int SSL_connect(SSL *ssl)
    {
      typename Mutex::scoped_lock lock(ssl_mutex_);
      return ::SSL_connect(ssl);
    }

  
    static int SSL_shutdown(SSL *ssl)
    {
      typename Mutex::scoped_lock lock(ssl_mutex_);
      return ::SSL_shutdown(ssl);  
    }

  openssl_context_service(boost::asio::io_service& io_service)
    : boost::asio::detail::service_base<openssl_context_service>(io_service)
  {
  }

  void shutdown_service()
  {
  }

  static impl_type null()
  {
    return 0;
  }

  void create(impl_type& impl, context_base::method m)
  {
    switch (m)
    {
#if defined(OPENSSL_NO_SSL2)
    case context_base::sslv2:
    case context_base::sslv2_client:
    case context_base::sslv2_server:
      boost::asio::detail::throw_error(boost::asio::error::invalid_argument);
      break;
#else // defined(OPENSSL_NO_SSL2)
    case context_base::sslv2:
      impl = ::SSL_CTX_new(::SSLv2_method());
      break;
    case context_base::sslv2_client:
      impl = ::SSL_CTX_new(::SSLv2_client_method());
      break;
    case context_base::sslv2_server:
      impl = ::SSL_CTX_new(::SSLv2_server_method());
      break;
#endif // defined(OPENSSL_NO_SSL2)
    case context_base::sslv3:
      impl = ::SSL_CTX_new(::SSLv3_method());
      break;
    case context_base::sslv3_client:
      impl = ::SSL_CTX_new(::SSLv3_client_method());
      break;
    case context_base::sslv3_server:
      impl = ::SSL_CTX_new(::SSLv3_server_method());
      break;
    case context_base::tlsv1:
      impl = ::SSL_CTX_new(::TLSv1_method());
      break;
    case context_base::tlsv1_client:
      impl = ::SSL_CTX_new(::TLSv1_client_method());
      break;
    case context_base::tlsv1_server:
      impl = ::SSL_CTX_new(::TLSv1_server_method());
      break;
    case context_base::sslv23:
      impl = ::SSL_CTX_new(::SSLv23_method());
      break;
    case context_base::sslv23_client:
      impl = ::SSL_CTX_new(::SSLv23_client_method());
      break;
    case context_base::sslv23_server:
      impl = ::SSL_CTX_new(::SSLv23_server_method());
      break;
    default:
      impl = ::SSL_CTX_new(0);
      break;
    }
  }

  void destroy(impl_type& impl)
  {
    if (impl != null())
    {
      if (impl->default_passwd_callback_userdata)
      {
        password_callback_type* callback =
          static_cast<password_callback_type*>(
              impl->default_passwd_callback_userdata);
        delete callback;
        impl->default_passwd_callback_userdata = 0;
      }

      ::SSL_CTX_free(impl);
      impl = null();
    }
  }

  boost::system::error_code set_options(impl_type& impl,
      context_base::options o, boost::system::error_code& ec)
  {
    ::SSL_CTX_set_options(impl, o);

    ec = boost::system::error_code();
    return ec;
  }

  boost::system::error_code set_verify_mode(impl_type& impl,
      context_base::verify_mode v, boost::system::error_code& ec)
  {
    ::SSL_CTX_set_verify(impl, v, 0);

    ec = boost::system::error_code();
    return ec;
  }

  boost::system::error_code load_verify_file(impl_type& impl,
      const std::string& filename, boost::system::error_code& ec)
  {
    if (::SSL_CTX_load_verify_locations(impl, filename.c_str(), 0) != 1)
    {
      ec = boost::asio::error::invalid_argument;
      return ec;
    }

    ec = boost::system::error_code();
    return ec;
  }

  boost::system::error_code add_verify_path(impl_type& impl,
      const std::string& path, boost::system::error_code& ec)
  {
    if (::SSL_CTX_load_verify_locations(impl, 0, path.c_str()) != 1)
    {
      ec = boost::asio::error::invalid_argument;
      return ec;
    }

    ec = boost::system::error_code();
    return ec;
  }

  boost::system::error_code use_certificate_file(impl_type& impl,
      const std::string& filename, context_base::file_format format,
      boost::system::error_code& ec)
  {
    int file_type;
    switch (format)
    {
    case context_base::asn1:
      file_type = SSL_FILETYPE_ASN1;
      break;
    case context_base::pem:
      file_type = SSL_FILETYPE_PEM;
      break;
    default:
      {
        ec = boost::asio::error::invalid_argument;
        return ec;
      }
    }

    if (::SSL_CTX_use_certificate_file(impl, filename.c_str(), file_type) != 1)
    {
      ec = boost::asio::error::invalid_argument;
      return ec;
    }

    ec = boost::system::error_code();
    return ec;
  }

  boost::system::error_code use_certificate_chain_file(impl_type& impl,
      const std::string& filename, boost::system::error_code& ec)
  {
    if (::SSL_CTX_use_certificate_chain_file(impl, filename.c_str()) != 1)
    {
      ec = boost::asio::error::invalid_argument;
      return ec;
    }

    ec = boost::system::error_code();
    return ec;
  }

  boost::system::error_code use_private_key_file(impl_type& impl,
      const std::string& filename, context_base::file_format format,
      boost::system::error_code& ec)
  {
    int file_type;
    switch (format)
    {
    case context_base::asn1:
      file_type = SSL_FILETYPE_ASN1;
      break;
    case context_base::pem:
      file_type = SSL_FILETYPE_PEM;
      break;
    default:
      {
        ec = boost::asio::error::invalid_argument;
        return ec;
      }
    }

    if (::SSL_CTX_use_PrivateKey_file(impl, filename.c_str(), file_type) != 1)
    {
      ec = boost::asio::error::invalid_argument;
      return ec;
    }

    ec = boost::system::error_code();
    return ec;
  }

  boost::system::error_code use_rsa_private_key_file(impl_type& impl,
      const std::string& filename, context_base::file_format format,
      boost::system::error_code& ec)
  {
    int file_type;
    switch (format)
    {
    case context_base::asn1:
      file_type = SSL_FILETYPE_ASN1;
      break;
    case context_base::pem:
      file_type = SSL_FILETYPE_PEM;
      break;
    default:
      {
        ec = boost::asio::error::invalid_argument;
        return ec;
      }
    }

    if (::SSL_CTX_use_RSAPrivateKey_file(
          impl, filename.c_str(), file_type) != 1)
    {
      ec = boost::asio::error::invalid_argument;
      return ec;
    }

    ec = boost::system::error_code();
    return ec;
  }

  boost::system::error_code use_tmp_dh_file(impl_type& impl,
      const std::string& filename, boost::system::error_code& ec)
  {
    ::BIO* bio = ::BIO_new_file(filename.c_str(), "r");
    if (!bio)
    {
      ec = boost::asio::error::invalid_argument;
      return ec;
    }

    ::DH* dh = ::PEM_read_bio_DHparams(bio, 0, 0, 0);
    if (!dh)
    {
      ::BIO_free(bio);
      ec = boost::asio::error::invalid_argument;
      return ec;
    }

    ::BIO_free(bio);
    int result = ::SSL_CTX_set_tmp_dh(impl, dh);
    ::DH_free(dh);
    if (result != 1)
    {
      ec = boost::asio::error::invalid_argument;
      return ec;
    }

    ec = boost::system::error_code();
    return ec;
  }


  static int password_callback(char* buf, int size, int purpose, void* data)
  {
    using namespace std; // For strncat and strlen.

    if (data)
    {
      password_callback_type* callback =
        static_cast<password_callback_type*>(data);
      std::string passwd = (*callback)(static_cast<std::size_t>(size),
          purpose ? context_base::for_writing : context_base::for_reading);
      *buf = '\0';
      strncat(buf, passwd.c_str(), size);
      return strlen(buf);
    }

    return 0;
  }

  template <typename Password_Callback>
  boost::system::error_code set_password_callback(impl_type& impl,
      Password_Callback callback, boost::system::error_code& ec)
  {
    // Allocate callback function object if not already present.
    if (impl->default_passwd_callback_userdata)
    {
      password_callback_type* callback_function =
        static_cast<password_callback_type*>(
            impl->default_passwd_callback_userdata);
      *callback_function = callback;
    }
    else
    {
      password_callback_type* callback_function =
        new password_callback_type(callback);
      impl->default_passwd_callback_userdata = callback_function;
    }

    // Set the password callback.
    SSL_CTX_set_default_passwd_cb(impl,
        &openssl_context_service::password_callback);

    ec = boost::system::error_code();
    return ec;
  }

  net_buffer()
  {
    data_start_ = data_end_ = buf_;
  }

  unsigned char* get_unused_start() { return data_end_; }

  unsigned char* get_data_start() { return data_start_; }

  size_t get_unused_len() { return (NET_BUF_SIZE - (data_end_ - buf_)); }
    
  size_t get_data_len() { return (data_end_ - data_start_); }
    
  void data_added(size_t count)
  { 
    data_end_ += count; 
    data_end_ = data_end_ > (buf_ + NET_BUF_SIZE)? 
      (buf_ + NET_BUF_SIZE):
      data_end_; 
  }

  void data_removed(size_t count) 
  { 
    data_start_ += count; 
    if (data_start_ >= data_end_) reset(); 
  }

  void reset() { data_start_ = buf_; data_end_ = buf_; }
               
  bool has_data() { return (data_start_ < data_end_); }

  openssl_operation(ssl_primitive_func primitive,
                    Stream& socket,
                    net_buffer& recv_buf,
                    SSL* session,
                    BIO* ssl_bio,
                    user_handler_func  handler,
                    boost::asio::io_service::strand& strand
                    )
    : primitive_(primitive)
    , user_handler_(handler)
    , strand_(&strand)
    , recv_buf_(recv_buf)
    , socket_(socket)
    , ssl_bio_(ssl_bio)
    , session_(session)
  {
    write_ = boost::bind(
      &openssl_operation::do_async_write, 
      this, boost::arg<1>(), boost::arg<2>()
    );
    read_ = boost::bind(
      &openssl_operation::do_async_read, 
      this
    );
    handler_= boost::bind(
      &openssl_operation::async_user_handler, 
      this, boost::arg<1>(), boost::arg<2>()
    );
  }

  int start()
  {
    int rc = primitive_( session_ );

    bool is_operation_done = (rc > 0);  
                // For connect/accept/shutdown, the operation
                // is done, when return code is 1
                // for write, it is done, when is retcode > 0
                // for read, it is done when retcode > 0

    int error_code =  !is_operation_done ?
          ::SSL_get_error( session_, rc ) :
          0;        
    int sys_error_code = ERR_get_error();

    if (error_code == SSL_ERROR_SSL)
      return handler_(boost::system::error_code(
            sys_error_code, boost::asio::error::get_ssl_category()), rc);

    bool is_read_needed = (error_code == SSL_ERROR_WANT_READ);
    bool is_write_needed = (error_code == SSL_ERROR_WANT_WRITE ||
                              ::BIO_ctrl_pending( ssl_bio_ ));
    bool is_shut_down_received = 
      ((::SSL_get_shutdown( session_ ) & SSL_RECEIVED_SHUTDOWN) == 
          SSL_RECEIVED_SHUTDOWN);
    bool is_shut_down_sent = 
      ((::SSL_get_shutdown( session_ ) & SSL_SENT_SHUTDOWN) ==
            SSL_SENT_SHUTDOWN);

    if (is_shut_down_sent && is_shut_down_received
        && is_operation_done && !is_write_needed)
      // SSL connection is shut down cleanly
      return handler_(boost::system::error_code(), 1);

    if (is_shut_down_received && !is_operation_done)
      // Shutdown has been requested, while we were reading or writing...
      // abort our action...
      return handler_(boost::asio::error::shut_down, 0);

    if (!is_operation_done && !is_read_needed && !is_write_needed 
      && !is_shut_down_sent)
    {
      // The operation has failed... It is not completed and does 
      // not want network communication nor does want to send shutdown out...
      if (error_code == SSL_ERROR_SYSCALL)
      {
        return handler_(boost::system::error_code(
              sys_error_code, boost::asio::error::system_category), rc); 
      }
      else
      {
        return handler_(boost::system::error_code(
              sys_error_code, boost::asio::error::get_ssl_category()), rc); 
      }
    }

    if (!is_operation_done && !is_write_needed)
    {
      // We may have left over data that we can pass to SSL immediately
      if (recv_buf_.get_data_len() > 0)
      {
        // Pass the buffered data to SSL
        int written = ::BIO_write
        ( 
          ssl_bio_, 
          recv_buf_.get_data_start(), 
          recv_buf_.get_data_len() 
        );

        if (written > 0)
        {
          recv_buf_.data_removed(written);
        }
        else if (written < 0)
        {
          if (!BIO_should_retry(ssl_bio_))
          {
            // Some serios error with BIO....
            return handler_(boost::asio::error::no_recovery, 0);
          }
        }

        return start();
      }
      else if (is_read_needed || (is_shut_down_sent && !is_shut_down_received))
      {
        return read_();
      }
    }

    // Continue with operation, flush any SSL data out to network...
    return write_(is_operation_done, rc); 
  }

  int sync_user_handler(const boost::system::error_code& error, int rc)
  {
    if (!error)
      return rc;

    throw boost::system::system_error(error);
  }

    
  int async_user_handler(boost::system::error_code error, int rc)
  {
    if (rc < 0)
    {
      if (!error)
        error = boost::asio::error::no_recovery;
      rc = 0;
    }

    user_handler_(error, rc);
    return 0;
  }

  int  do_async_write(bool is_operation_done, int rc) 
  {
    int len = ::BIO_ctrl_pending( ssl_bio_ );
    if ( len )
    { 
      // There is something to write into net, do it...
      len = (int)send_buf_.get_unused_len() > len? 
        len: 
        send_buf_.get_unused_len();
        
      if (len == 0)
      {
        // In case our send buffer is full, we have just to wait until 
        // previous send to complete...
        return 0;
      }

      // Read outgoing data from bio
      len = ::BIO_read( ssl_bio_, send_buf_.get_unused_start(), len); 
         
      if (len > 0)
      {
        unsigned char *data_start = send_buf_.get_unused_start();
        send_buf_.data_added(len);
 
        BOOST_ASIO_ASSERT(strand_);
        boost::asio::async_write
        ( 
          socket_, 
          boost::asio::buffer(data_start, len),
          strand_->wrap
          (
            boost::bind
            (
              &openssl_operation::async_write_handler, 
              this, 
              is_operation_done,
              rc, 
              boost::asio::placeholders::error, 
              boost::asio::placeholders::bytes_transferred
            )
          )
        );
                  
        return 0;
      }
      else if (!BIO_should_retry(ssl_bio_))
      {
        // Seems like fatal error
        // reading from SSL BIO has failed...
        handler_(boost::asio::error::no_recovery, 0);
        return 0;
      }
    }
    
    if (is_operation_done)
    {
      // Finish the operation, with success
      handler_(boost::system::error_code(), rc);
      return 0;
    }
    
    // OPeration is not done and writing to net has been made...
    // start operation again
    start();
          
    return 0;
  }


  void async_write_handler(bool is_operation_done, int rc, 
    const boost::system::error_code& error, size_t bytes_sent)
  {
    if (!error)
    {
      // Remove data from send buffer
      send_buf_.data_removed(bytes_sent);

      if (is_operation_done)
        handler_(boost::system::error_code(), rc);
      else
        // Since the operation was not completed, try it again...
        start();
    }
    else 
      handler_(error, rc);
  }


  int do_async_read()
  {
    // Wait for new data
    BOOST_ASIO_ASSERT(strand_);
    socket_.async_read_some
    ( 
      boost::asio::buffer(recv_buf_.get_unused_start(),
        recv_buf_.get_unused_len()),
      strand_->wrap
      (
        boost::bind
        (
          &openssl_operation::async_read_handler, 
          this, 
          boost::asio::placeholders::error, 
          boost::asio::placeholders::bytes_transferred
        )
      )
    );
    return 0;
  }


  void async_read_handler(const boost::system::error_code& error,
      size_t bytes_recvd)
  {
    if (!error)
    {
      recv_buf_.data_added(bytes_recvd);

      // Pass the received data to SSL
      int written = ::BIO_write
      ( 
        ssl_bio_, 
        recv_buf_.get_data_start(), 
        recv_buf_.get_data_len() 
      );

      if (written > 0)
      {
        recv_buf_.data_removed(written);
      }
      else if (written < 0)
      {
        if (!BIO_should_retry(ssl_bio_))
        {
          // Some serios error with BIO....
          handler_(boost::asio::error::no_recovery, 0);
          return;
        }
      }

      // and try the SSL primitive again
      start();
    }
    else
    {
      // Error in network level...
      // SSL can't continue either...
      handler_(error, 0);
    }
  }

  int do_sync_write(bool is_operation_done, int rc)
  {
    int len = ::BIO_ctrl_pending( ssl_bio_ );
    if ( len )
    { 
      // There is something to write into net, do it...
      len = (int)send_buf_.get_unused_len() > len? 
        len: 
        send_buf_.get_unused_len();
        
      // Read outgoing data from bio
      len = ::BIO_read( ssl_bio_, send_buf_.get_unused_start(), len); 
         
      if (len > 0)
      {
        size_t sent_len = boost::asio::write( 
                  socket_, 
                  boost::asio::buffer(send_buf_.get_unused_start(), len)
                  );

        send_buf_.data_added(len);
        send_buf_.data_removed(sent_len);
      }          
      else if (!BIO_should_retry(ssl_bio_))
      {
        // Seems like fatal error
        // reading from SSL BIO has failed...
        throw boost::system::system_error(boost::asio::error::no_recovery);
      }
    }
    
    if (is_operation_done)
      // Finish the operation, with success
      return rc;
                
    // Operation is not finished, start again.
    return start();
  }


  int do_sync_read()
  {
    size_t len = socket_.read_some
      ( 
        boost::asio::buffer(recv_buf_.get_unused_start(),
          recv_buf_.get_unused_len())
      );

    // Write data to ssl
    recv_buf_.data_added(len);

    // Pass the received data to SSL
    int written = ::BIO_write
    ( 
      ssl_bio_, 
      recv_buf_.get_data_start(), 
      recv_buf_.get_data_len() 
    );

    if (written > 0)
    {
      recv_buf_.data_removed(written);
    }
    else if (written < 0)
    {
      if (!BIO_should_retry(ssl_bio_))
      {
        // Some serios error with BIO....
        throw boost::system::system_error(boost::asio::error::no_recovery);
      }
    }

    // Try the operation again
    return start();
  }
