

  inline bool type_present(file_status f) { return f.type() != status_error; }

  inline bool permissions_present(file_status f)
                                          {return f.permissions() != perms_not_known;}

  inline bool status_known(file_status f) { return type_present(f) && permissions_present(f); }

  inline bool exists(file_status f)       { return f.type() != status_error
                                                && f.type() != file_not_found; }

  inline bool is_regular_file(file_status f){ return f.type() == regular_file; }

  inline bool is_directory(file_status f) { return f.type() == directory_file; }

  inline bool is_symlink(file_status f)   { return f.type() == symlink_file; }

  inline bool is_other(file_status f)     { return exists(f) && !is_regular_file(f)
                                                && !is_directory(f) && !is_symlink(f); }

  inline bool is_regular(file_status f)   { return f.type() == regular_file; }


  inline
  file_status status(const path& p)    {return detail::status(p);}

  inline 
  file_status symlink_status(const path& p) {return detail::symlink_status(p);}


  inline
  bool is_empty(const path& p)         {return detail::is_empty(p);}


  inline
  path canonical(const path& p, const path& base=current_path())
                                       {return detail::canonical(p, base);}

  inline
  path complete(const path& p)
  {
    return absolute(p, initial_path());
  }


  inline
  void copy(const path& from, const path& to) {detail::copy(from, to);}

  inline
  void copy_directory(const path& from, const path& to)
                                       {detail::copy_directory(from, to);}

  inline
  void copy_file(const path& from, const path& to,   // See ticket #2925
                 BOOST_SCOPED_ENUM(copy_option) option)
                                       {detail::copy_file(from, to, option);}

  inline
  void copy_symlink(const path& existing_symlink, const path& new_symlink) {detail::copy_symlink(existing_symlink, new_symlink);}

  inline
  bool create_directories(const path& p) {return detail::create_directories(p);}

  inline
  bool create_directory(const path& p) {return detail::create_directory(p);}

  inline
  void create_directory_symlink(const path& to, const path& from)
                                       {detail::create_directory_symlink(to, from);}

  inline
  void create_hard_link(const path& to, const path& new_hard_link) {detail::create_hard_link(to, new_hard_link);}

  inline
  void create_symlink(const path& to, const path& new_symlink) {detail::create_symlink(to, new_symlink);}


  inline
  bool equivalent(const path& p1, const path& p2) {return detail::equivalent(p1, p2);}

  inline
  boost::uintmax_t file_size(const path& p) {return detail::file_size(p);}

  inline
  boost::uintmax_t hard_link_count(const path& p) {return detail::hard_link_count(p);}


  inline
  std::time_t last_write_time(const path& p) {return detail::last_write_time(p);}

  inline
  void permissions(const path& p, perms prms)
                                       {detail::permissions(p, prms);}


  inline
  path read_symlink(const path& p)     {return detail::read_symlink(p);}

  inline
    // For standardization, if the committee doesn't like "remove", consider "eliminate"
  bool remove(const path& p)           {return detail::remove(p);}


  inline
  boost::uintmax_t remove_all(const path& p) {return detail::remove_all(p);}

  inline
  void rename(const path& old_p, const path& new_p) {detail::rename(old_p, new_p);}

  inline  // name suggested by Scott McMurray
  void resize_file(const path& p, uintmax_t size) {detail::resize_file(p, size);}

  inline
  space_info space(const path& p)      {return detail::space(p);}

  inline bool symbolic_link_exists(const path& p)
                                       { return is_symlink(symlink_status(p)); }


  inline
  path system_complete(const path& p)  {return detail::system_complete(p);}

  inline
  path temp_directory_path()           {return detail::temp_directory_path();}

  inline
  path unique_path(const path& p="%%%%-%%%%-%%%%-%%%%")
                                       { return detail::unique_path(p); }


    dir_itr_imp() : handle(0)
#   ifdef BOOST_POSIX_API
      , buffer(0)
#   endif
    {}


    ~dir_itr_imp() // never throws
    {
      dir_itr_close(handle
#       if defined(BOOST_POSIX_API)
         , buffer
#       endif
    );
    }


    directory_iterator(){}


   ~directory_iterator() {}


    directory_iterator& increment(system::error_code& ec)
    { 
      detail::directory_iterator_increment(*this, &ec);
      return *this;
    }


    inline std::string extension(const path & p)
    {
      return p.extension().string();
    }


    inline std::string basename(const path & p)
    {
      return p.stem().string();
    }


    inline path change_extension( const path & p, const path & new_extension )
    { 
      path new_p( p );
      new_p.replace_extension( new_extension );
      return new_p;
    }


  inline 
  void convert(const char* from,
                std::wstring & to,
                const codecvt_type& cvt)
  {
    BOOST_ASSERT(from);
    convert(from, 0, to, cvt);
  }

  template <class U> inline
    void dispatch(const std::string& c, U& to, const codecvt_type& cvt)
  {
    if (c.size())
      convert(&*c.begin(), &*c.begin() + c.size(), to, cvt);
  }


    const path& dereference() const { return m_element; }


    bool equal(const iterator & rhs) const
    {
      return m_path_ptr == rhs.m_path_ptr && m_pos == rhs.m_pos;
    }

    void increment() { m_path_iterator_increment(*this); }

    void decrement() { m_path_iterator_decrement(*this); }

  inline bool lexicographical_compare(path::iterator first1, path::iterator last1,
    path::iterator first2, path::iterator last2)
    { return detail::lex_compare(first1, last1, first2, last2) < 0; }

  
  inline bool operator==(const path& lhs, const path& rhs)              {return lhs.compare(rhs) == 0;}

  
  inline bool operator!=(const path& lhs, const path& rhs)              {return lhs.compare(rhs) != 0;}


  inline bool operator<(const path& lhs, const path& rhs)  {return lhs.compare(rhs) < 0;}

  inline bool operator<=(const path& lhs, const path& rhs) {return !(rhs < lhs);}

  inline bool operator> (const path& lhs, const path& rhs) {return rhs < lhs;}

  inline bool operator>=(const path& lhs, const path& rhs) {return !(lhs < rhs);}


  inline std::size_t hash_value(const path& x)
  {
# ifdef BOOST_WINDOWS_API
    std::size_t seed = 0;
    for(const path::value_type* it = x.c_str(); *it; ++it)
      hash_combine(seed, *it == '/' ? L'\\' : *it);
    return seed;
# else   // BOOST_POSIX_API
    return hash_range(x.native().begin(), x.native().end());
# endif
  }


  template <class InputIterator>
  path& path::append(InputIterator begin, InputIterator end, const codecvt_type& cvt)
  { 
    if (begin == end)
      return *this;
    string_type::size_type sep_pos(m_append_separator_if_needed());
    std::basic_string<typename std::iterator_traits<InputIterator>::value_type>
      s(begin, end);
    path_traits::convert(s.c_str(), s.c_str()+s.size(), m_pathname, cvt);
    if (sep_pos)
      m_erase_redundant_separator(sep_pos);
    return *this;
  }
