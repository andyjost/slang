 skeleton(T& x)
{
  return skeleton_proxy<T>(x);
}

template<typename T> MPI_Datatype get_mpi_datatype(const T& x)
{
  BOOST_MPL_ASSERT((is_mpi_datatype<T>));
  return detail::mpi_datatype_cache().datatype(x);
}

  inline MPI_Datatype build_mpi_datatype_for_bool()
  {
    MPI_Datatype type;
    MPI_Type_contiguous(sizeof(bool), MPI_BYTE, &type);
    MPI_Type_commit(&type);
    return type;
  }

  const T& operator()(const T& x, const T& y) const
  {
    return x < y? y : x;
  }

  const T& operator()(const T& x, const T& y) const
  {
    return x < y? x : y;
  }

  T operator()(const T& x, const T& y) const
  {
    return x & y;
  }

  T operator()(const T& x, const T& y) const
  {
    return x | y;
  }

  T operator()(const T& x, const T& y) const
  {
    return (x || y) && !(x && y);
  }

  T operator()(const T& x, const T& y) const
  {
    return x ^ y;
  }

  static MPI_Op op() { return MPI_MAX; }

  static MPI_Op op() { return MPI_MIN; }

  static MPI_Op op() { return MPI_LXOR; }

  static MPI_Op op() { return MPI_BAND; }

  static MPI_Op op() { return MPI_BOR; }

  static MPI_Op op() { return MPI_BXOR; }

    explicit user_op(Op& op)
    {
      BOOST_MPI_CHECK_RESULT(MPI_Op_create,
                             (&user_op<Op, T>::perform,
                              is_commutative<Op, T>::value,
                              &mpi_op));

      op_ptr = &op;
    }


    ~user_op()
    {
      if (std::uncaught_exception()) {
        // Ignore failure cases: there are obviously other problems
        // already, and we don't want to cause program termination if
        // MPI_Op_free fails.
        MPI_Op_free(&mpi_op);
      } else {
        BOOST_MPI_CHECK_RESULT(MPI_Op_free, (&mpi_op));
      }
    }


    MPI_Op& get_mpi_op()
    {
      return mpi_op;
    }

inline bool operator!=(const communicator& comm1, const communicator& comm2)
{
  return !(comm1 == comm2);
}

inline bool operator!=(const group& g1, const group& g2)
{ 
  return !(g1 == g2);
}

inline int num_vertices(const graph_communicator& comm) { return comm.size(); }

inline identity_property_map get(vertex_index_t, const graph_communicator&)
{
  return identity_property_map();
}

  static vertex_descriptor null_vertex() { return -1; }

    ignore_iprimitive()
    {}

    void load_binary(void *, std::size_t )
        {}

    template<class T>
    void load_array(serialization::array<T> &, unsigned int )
    {}

    template<class T>
    void load(T & t)
    {
    }

    ignore_skeleton_oarchive()
      : archive::detail::common_oarchive<Archive>(archive::no_header)
    {
    }

    template<class T>
    void save_override(T const& t, BOOST_PFTO int)
    {
        archive::save(* this->This(), t);
    }

    forward_iprimitive(implementation_archive_type& ar)
     : implementation_archive(ar)
    {}

    void load_binary(void * address, std::size_t count )
    {
      implementation_archive.load_binary(address,count);
    }

    template<class T>
    void load_array(serialization::array<T> & x, unsigned int file_version )
    {
      implementation_archive.load_array(x,file_version);
    }

    template<class T>
    void load(T & t)
    {
      implementation_archive >> t;
    }

    forward_oprimitive(implementation_archive_type& ar)
     : implementation_archive(ar)
    {}

    void save_binary(const void * address, std::size_t count)
    {
      implementation_archive.save_binary(address,count);
    }

    template<class T>
    void save_array(serialization::array<T> const& x, unsigned int file_version )
    {
      implementation_archive.save_array(x,file_version);
    }

    template<class T>
    void save(const T & t)
    {
      implementation_archive << t;
    }

    mpi_datatype_primitive()
     : is_committed(false),
       origin(0)
    {}


    mpi_datatype_primitive(void const* orig)
     : is_committed(false),
       origin()
    {
      BOOST_MPI_CHECK_RESULT(MPI_Address,(const_cast<void*>(orig), &origin));
    }


    void save_binary(void const *address, std::size_t count)
    {
      save_impl(address,MPI_BYTE,count);
    }

    template<class T>
    void save_array(serialization::array<T> const& x, unsigned int /* version */)
    {
      if (x.count())
        save_impl(x.address(), boost::mpi::get_mpi_datatype(*x.address()), x.count());
    }

    MPI_Datatype get_mpi_datatype()
    {
      if (!is_committed)
      {
        BOOST_MPI_CHECK_RESULT(MPI_Type_struct,
                    (
                      addresses.size(),
                      boost::serialization::detail::get_data(lengths),
                      boost::serialization::detail::get_data(addresses),
                      boost::serialization::detail::get_data(types),
                      &datatype_
                    ));

        BOOST_MPI_CHECK_RESULT(MPI_Type_commit,(&datatype_));

        is_committed = true;
      }

      return datatype_;
    }

    template<class T>
    void save(const T & t)
    {
        save_impl(&t, boost::mpi::get_mpi_datatype(t), 1);
    }


    void save_impl(void const * p, MPI_Datatype t, int l)
    {
      BOOST_ASSERT ( !is_committed );

      // store address, type and length

      MPI_Aint a;
      BOOST_MPI_CHECK_RESULT(MPI_Address,(const_cast<void*>(p), &a));

      addresses.push_back(a-origin);
      types.push_back(t);
      lengths.push_back(l);
    }

  bool operator()(std::type_info const* lhs, std::type_info const* rhs) const
  {
    return lhs->before(*rhs);
  }

  int branching_factor() const { return branching_factor_; }

  int level() const { return level_; }


template<typename T>
inline void
broadcast(const communicator& comm, skeleton_proxy<T>& proxy, int root)
{
  const skeleton_proxy<T>& const_proxy(proxy);
  broadcast(comm, const_proxy, root);
}

    ignore_oprimitive()
    {}

    void save_binary(const void *, std::size_t )
    {
    }

    template<class T>
    void save_array(serialization::array<T> const&, unsigned int )
    {
    }

    template<class T>
    void save(const T & t)
    {
    }


    forward_skeleton_iarchive(implementation_archive_type& ar) 
      : archive::detail::common_iarchive<Archive>(archive::no_header),
        implementation_archive(ar)
    {
    }

    template<class T>
    void load_override(T & t, BOOST_PFTO int)
    {
        archive::load(* this->This(), t);
    }

    text_skeleton_oarchive(std::ostream & s, unsigned int flags = 0) 
     : detail::forward_skeleton_oarchive<text_skeleton_oarchive,boost::archive::text_oarchive>(skeleton_archive_)
     , skeleton_archive_(s,flags)
    {}


template <class T>
const content get_content(const T& x)
{
  detail::content_oarchive ar;
  ar << x;
  return ar.get_content();
}

    template <class T>
    mpi_datatype_oarchive(const T& x)
         :  mpi_datatype_primitive(&x) // register address
        {
          BOOST_MPL_ASSERT((is_mpi_datatype<T>));
          *this << x;                   // serialize the object
        }

    template<class T>
    void save_override(T const& t, BOOST_PFTO int)
    {
      save_enum(t,boost::is_enum<T>());
    }


    template<class T>
    void save_enum(T const& t, mpl::false_)
    {
      ignore_skeleton_oarchive<mpi_datatype_oarchive>::save_override(t, 0);
    }


    forward_skeleton_oarchive(implementation_archive_type& ar) 
      : archive::detail::common_oarchive<Archive>(archive::no_header),
        implementation_archive(ar)
    {
    }

    template<class T>
    void save_override(T const& t, BOOST_PFTO int)
    {
        archive::save(* this->This(), t);
    }

  template<typename T, typename Op>
  void
  scan_impl(const communicator& comm, const T* in_values, int n, T* out_values,
            Op op, mpl::true_ /*is_mpi_op*/, mpl::true_ /*is_mpi_datatype*/)
  {
    BOOST_MPI_CHECK_RESULT(MPI_Scan,
                           (const_cast<T*>(in_values), out_values, n,
                            boost::mpi::get_mpi_datatype<T>(*in_values),
                            (is_mpi_op<Op, T>::op()), comm));
  }


  template<typename T, typename Op>
  void
  upper_lower_scan(const communicator& comm, const T* in_values, int n,
                   T* out_values, Op& op, int lower, int upper)
  {
    int tag = environment::collectives_tag();
    int rank = comm.rank();

    if (lower + 1 == upper) {
      std::copy(in_values, in_values + n, out_values);
    } else {
      int middle = (lower + upper) / 2;
      
      if (rank < middle) {
        // Lower half
        upper_lower_scan(comm, in_values, n, out_values, op, lower, middle);

        // If we're the last process in the lower half, send our values
        // to everyone in the upper half.
        if (rank == middle - 1) {
          packed_oarchive oa(comm);
          for (int i = 0; i < n; ++i)
            oa << out_values[i];

          for (int p = middle; p < upper; ++p)
            comm.send(p, tag, oa);
        }
      } else {
        // Upper half
        upper_lower_scan(comm, in_values, n, out_values, op, middle, upper);

        // Receive value from the last process in the lower half.
        packed_iarchive ia(comm);
        comm.recv(middle - 1, tag, ia);

        // Combine value that came from the left with our value
        T left_value;
        for (int i = 0; i < n; ++i)
          {
            ia >> left_value;
            out_values[i] = op(left_value, out_values[i]);
          }
      }
    }
  }



template<typename T, typename Op>
inline void
scan(const communicator& comm, const T& in_value, T& out_value, Op op)
{
  detail::scan_impl(comm, &in_value, 1, &out_value, op, 
                    is_mpi_op<Op, T>(), is_mpi_datatype<T>());
}

  template<typename T>
  void
  scatter_impl(const communicator& comm, const T* in_values, T* out_values, 
               int n, int root, mpl::true_)
  {
    MPI_Datatype type = get_mpi_datatype<T>(*in_values);
    BOOST_MPI_CHECK_RESULT(MPI_Scatter,
                           (const_cast<T*>(in_values), n, type,
                            out_values, n, type, root, comm));
  }


template<typename T>
void
scatter(const communicator& comm, const T* in_values, T& out_value, int root)
{
  if (comm.rank() == root)
    detail::scatter_impl(comm, in_values, &out_value, 1, root, 
                         is_mpi_datatype<T>());
  else
    detail::scatter_impl(comm, &out_value, 1, root, is_mpi_datatype<T>());
}

  template<typename T>
  void
  all_gather_impl(const communicator& comm, const T* in_values, int n, 
                  T* out_values, mpl::true_)
  {
    MPI_Datatype type = boost::mpi::get_mpi_datatype<T>(*in_values);
    BOOST_MPI_CHECK_RESULT(MPI_Allgather,
                           (const_cast<T*>(in_values), n, type,
                            out_values, n, type, comm));
  }


template<typename T>
inline void
all_gather(const communicator& comm, const T& in_value, T* out_values)
{
  detail::all_gather_impl(comm, &in_value, 1, out_values, is_mpi_datatype<T>());
}

  template<typename T, typename Op>
  void
  reduce_impl(const communicator& comm, const T* in_values, int n, 
              T* out_values, Op op, int root, mpl::true_ /*is_mpi_op*/,
              mpl::true_/*is_mpi_datatype*/)
  {
    BOOST_MPI_CHECK_RESULT(MPI_Reduce,
                           (const_cast<T*>(in_values), out_values, n,
                            boost::mpi::get_mpi_datatype<T>(*in_values),
                            (is_mpi_op<Op, T>::op()), root, comm));
  }

  template<typename T, typename Op>
  void
  tree_reduce_impl(const communicator& comm, const T* in_values, int n,
                   T* out_values, Op op, int root, 
                   mpl::true_ /*is_commutative*/)
  {
    std::copy(in_values, in_values + n, out_values);

    int size = comm.size();
    int rank = comm.rank();

    // The computation tree we will use.
    detail::computation_tree tree(rank, size, root);

    int tag = environment::collectives_tag();

    MPI_Status status;
    int children = 0;
    for (int child = tree.child_begin();
         children < tree.branching_factor() && child != root;
         ++children, child = (child + 1) % size) {
      // Receive archive
      packed_iarchive ia(comm);
      detail::packed_archive_recv(comm, child, tag, ia, status);

      T incoming;
      for (int i = 0; i < n; ++i) {
        ia >> incoming;
        out_values[i] = op(out_values[i], incoming);
      }
    }

    // For non-roots, send the result to the parent.
    if (tree.parent() != rank) {
      packed_oarchive oa(comm);
      for (int i = 0; i < n; ++i)
        oa << out_values[i];
      detail::packed_archive_send(comm, tree.parent(), tag, oa);
    }
  }


template<typename T, typename Op>
void
reduce(const communicator& comm, const T* in_values, int n, T* out_values, 
       Op op, int root)
{
  if (comm.rank() == root)
    detail::reduce_impl(comm, in_values, n, out_values, op, root,
                        is_mpi_op<Op, T>(), is_mpi_datatype<T>());
  else
    detail::reduce_impl(comm, in_values, n, op, root,
                        is_mpi_op<Op, T>(), is_mpi_datatype<T>());
}

  template<typename T>
  void
  all_to_all_impl(const communicator& comm, const T* in_values, int n, 
                  T* out_values, mpl::true_)
  {
    MPI_Datatype type = get_mpi_datatype<T>(*in_values);
    BOOST_MPI_CHECK_RESULT(MPI_Alltoall,
                           (const_cast<T*>(in_values), n, type,
                            out_values, n, type, comm));
  }


template<typename T>
inline void
all_to_all(const communicator& comm, const T* in_values, T* out_values)
{
  detail::all_to_all_impl(comm, in_values, 1, out_values, is_mpi_datatype<T>());
}

  template<typename T>
  void
  gather_impl(const communicator& comm, const T* in_values, int n, 
              T* out_values, int root, mpl::true_)
  {
    MPI_Datatype type = get_mpi_datatype<T>(*in_values);
    BOOST_MPI_CHECK_RESULT(MPI_Gather,
                           (const_cast<T*>(in_values), n, type,
                            out_values, n, type, root, comm));
  }


template<typename T>
void
gather(const communicator& comm, const T& in_value, T* out_values, int root)
{
  if (comm.rank() == root)
    detail::gather_impl(comm, &in_value, 1, out_values, root, 
                        is_mpi_datatype<T>());
  else
    detail::gather_impl(comm, &in_value, 1, root, is_mpi_datatype<T>());
}

  template<typename T>
  void 
  broadcast_impl(const communicator& comm, T* values, int n, int root, 
                 mpl::true_)
  {
    BOOST_MPI_CHECK_RESULT(MPI_Bcast,
                           (values, n,
                            boost::mpi::get_mpi_datatype<T>(*values),
                            root, MPI_Comm(comm)));
  }

  template<typename T, typename Op>
  void
  all_reduce_impl(const communicator& comm, const T* in_values, int n,
                  T* out_values, Op /*op*/, mpl::true_ /*is_mpi_op*/,
                  mpl::true_ /*is_mpi_datatype*/)
  {
    BOOST_MPI_CHECK_RESULT(MPI_Allreduce,
                           (const_cast<T*>(in_values), out_values, n,
                            boost::mpi::get_mpi_datatype<T>(*in_values),
                            (is_mpi_op<Op, T>::op()), comm));
  }


template<typename T, typename Op>
inline void
all_reduce(const communicator& comm, const T* in_values, int n, T* out_values,
           Op op)
{
  detail::all_reduce_impl(comm, in_values, n, out_values, op,
                          is_mpi_op<Op, T>(), is_mpi_datatype<T>());
}

  content(const inherited& base, boost::python::object object) 
    : inherited(base), object(object) { }


  inherited&       base()       { return *this; }

  const inherited& base() const { return *this; }

  skeleton_proxy_base(const boost::python::object& object) : object(object) { }

  skeleton_proxy(const boost::python::object& object) 
    : skeleton_proxy_base(object) { }

    void 
    operator()(packed_oarchive& ar, const object& obj, const unsigned int)
    {
      packed_skeleton_oarchive pso(ar);
      pso << extract<T&>(obj.attr("object"))();
    }

    void 
    operator()(packed_iarchive& ar, object& obj, const unsigned int)
    {
      packed_skeleton_iarchive psi(ar);
      extract<skeleton_proxy<T>&> proxy(obj);
      if (!proxy.check())
        obj = object(skeleton_proxy<T>(object(T())));

      psi >> extract<T&>(obj.attr("object"))();
    }

    object operator()(object value) {
      return object(skeleton_proxy<T>(value));
    }

    content operator()(object value_obj) {
      T& value = extract<T&>(value_obj)();
      return content(boost::mpi::get_content(value), value_obj);
    }


template<typename T>
void register_skeleton_and_content(const T& value, PyTypeObject* type)
{
  using boost::python::detail::direct_serialization_table;
  using boost::python::detail::get_direct_serialization_table;
  using namespace boost::python;

  // Determine the type
  if (!type)
    type = object(value).ptr()->ob_type;

  // Don't re-register the same type.
  if (detail::skeleton_and_content_handler_registered(type))
    return;

  // Register the skeleton proxy type
  {
    boost::python::scope proxy_scope(detail::skeleton_proxy_base_type);
    std::string name("skeleton_proxy<");
    name += typeid(T).name();
    name += ">";
    class_<skeleton_proxy<T>, bases<skeleton_proxy_base> >(name.c_str(), 
                                                           no_init);
  }

  // Register the saver and loader for the associated skeleton and
  // proxy, to allow (de-)serialization of skeletons via the proxy.
  direct_serialization_table<packed_iarchive, packed_oarchive>& table = 
    get_direct_serialization_table<packed_iarchive, packed_oarchive>();
  table.register_type(detail::skeleton_saver<T>(), 
                      detail::skeleton_loader<T>(), 
                      skeleton_proxy<T>(object(value)));

  // Register the rest of the skeleton/content mechanism, including
  // handlers that extract a skeleton proxy from a Python object and
  // extract the content from a Python object.
  detail::skeleton_content_handler handler;
  handler.get_skeleton_proxy = detail::do_get_skeleton_proxy<T>();
  handler.get_content = detail::do_get_content<T>();
  detail::register_skeleton_and_content_handler(type, handler);
}

template<typename IArchiver, typename OArchiver, typename T>
void
register_serialized(const T& value = T(), PyTypeObject* type = 0)
{
  detail::direct_serialization_table<IArchiver, OArchiver>& table = 
    detail::get_direct_serialization_table<IArchiver, OArchiver>();
  table.register_type(value, type);
}

template<typename Archiver>
void 
save_impl(Archiver& ar, const boost::python::object& obj, 
          const unsigned int /*version*/,
          mpl::false_ /*has_direct_serialization*/)
{
  boost::python::str py_string = boost::python::pickle::dumps(obj);
  int len = boost::python::extract<int>(py_string.attr("__len__")());
  const char* string = boost::python::extract<const char*>(py_string);
  ar << len << boost::serialization::make_array(string, len);
}

template<typename Archiver>
void 
load_impl(Archiver& ar, boost::python::object& obj, 
          const unsigned int /*version*/, 
          mpl::false_ /*has_direct_serialization*/)
{
  int len;
  ar >> len;

  std::auto_ptr<char> string(new char[len]);
  ar >> boost::serialization::make_array(string.get(), len);
  boost::python::str py_string(string.get(), len);
  obj = boost::python::pickle::loads(py_string);
}


template<typename Archiver>
void 
save(Archiver& ar, const boost::python::object& obj, 
     const unsigned int version)
{
  typedef Archiver OArchiver;
  typedef typename input_archiver<OArchiver>::type IArchiver;

  detail::save_impl(ar, obj, version, 
                    has_direct_serialization<IArchiver, OArchiver>());
}


template<typename Archiver>
void 
load(Archiver& ar, boost::python::object& obj, 
     const unsigned int version)
{
  typedef Archiver IArchiver;
  typedef typename output_archiver<IArchiver>::type OArchiver;

  detail::load_impl(ar, obj, version, 
                    has_direct_serialization<IArchiver, OArchiver>());
}


template<typename Archive>
inline void 
serialize(Archive& ar, boost::python::object& obj, const unsigned int version)
{
  boost::serialization::split_free(ar, obj, version);
}


template<typename T>
void
register_serialized(const T& value, PyTypeObject* type)
{
  using boost::python::register_serialized;
  register_serialized<packed_iarchive, packed_oarchive>(value, type);
}
