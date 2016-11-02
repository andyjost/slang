
    inline bool validate_flags(int flags)
    {
        return flags == 0;
    }

        ini_parser_error(const std::string &message,
                         const std::string &filename,
                         unsigned long line)
            : file_parser_error(message, filename, line)
        {
        }

        template<class Ptree>
        void check_dupes(const Ptree &pt)
        {
            if(pt.size() <= 1)
                return;
            const typename Ptree::key_type *lastkey = 0;
            typename Ptree::const_assoc_iterator it = pt.ordered_begin(),
                                                 end = pt.not_found();
            lastkey = &it->first;
            for(++it; it != end; ++it) {
                if(*lastkey == it->first)
                    BOOST_PROPERTY_TREE_THROW(ini_parser_error(
                        "duplicate key", "", 0));
                lastkey = &it->first;
            }
        }

        static void insert(std::basic_ostream<Ch, Traits>& s, const E& e) {
            s << e;
        }

        static void extract(std::basic_istream<Ch, Traits>& s, E& e) {
            s >> e;
            if(!s.eof()) {
                s >> std::ws;
            }
        }

        static void insert(std::basic_ostream<Ch, Traits>& s, Ch e) {
            s << e;
        }

        static void extract(std::basic_istream<Ch, Traits>& s, Ch& e) {
            s.unsetf(std::ios_base::skipws);
            s >> e;
        }

        static void insert(std::basic_ostream<Ch, Traits>& s, bool e) {
            s.setf(std::ios_base::boolalpha);
            s << e;
        }

        static void extract(std::basic_istream<Ch, Traits>& s, bool& e) {
            s >> e;
            if(s.fail()) {
                // Try again in word form.
                s.clear();
                s.setf(std::ios_base::boolalpha);
                s >> e;
            }
            if(!s.eof()) {
                s >> std::ws;
            }
        }

        static void insert(std::basic_ostream<Ch, Traits>& s, signed char e) {
            s << (int)e;
        }

        static void extract(std::basic_istream<Ch, Traits>& s, signed char& e) {
            int i;
            s >> i;
            // out of range?
            if(i > (std::numeric_limits<signed char>::max)() ||
                i < (std::numeric_limits<signed char>::min)())
            {
                s.clear(); // guarantees eof to be unset
                return;
            }
            e = (signed char)i;
            if(!s.eof()) {
                s >> std::ws;
            }
        }

        static void insert(std::basic_ostream<Ch, Traits>& s, unsigned char e) {
            s << (unsigned)e;
        }

        static void extract(std::basic_istream<Ch,Traits>& s, unsigned char& e){
            unsigned i;
            s >> i;
            // out of range?
            if(i > (std::numeric_limits<unsigned char>::max)()) {
                s.clear(); // guarantees eof to be unset
                return;
            }
            e = (unsigned char)i;
            if(!s.eof()) {
                s >> std::ws;
            }
        }


        explicit stream_translator(std::locale loc = std::locale())
            : m_loc(loc)
        {}

        template <typename Sequence, typename Iterator>
        void append_and_preserve_iter(Sequence &s, const Sequence &r,
                                      Iterator &, std::forward_iterator_tag)
        {
            // Here we boldly assume that anything that is not random-access
            // preserves validity. This is valid for the STL sequences.
            s.insert(s.end(), r.begin(), r.end());
        }


        template <typename Sequence>
        inline std::string dump_sequence(const Sequence &)
        {
            return "<undumpable sequence>";
        }

        char_type separator() const { return m_separator; }


        std::string dump() const {
            return detail::dump_sequence(m_value);
        }

        string_path& operator /=(const string_path &o) {
            // If it's single, there's no separator. This allows to do
            // p /= "piece";
            // even for non-default separators.
            BOOST_ASSERT((m_separator == o.m_separator
                          || o.empty()
                          || o.single())
                         && "Incompatible paths.");
            if(!o.empty()) {
                String sub;
                if(!this->empty()) {
                    sub.push_back(m_separator);
                }
                sub.insert(sub.end(), o.cstart(), o.m_value.end());
                detail::append_and_preserve_iter(m_value, sub, m_start,
                    typename std::iterator_traits<s_iter>::iterator_category());
            }
            return *this;
        }

        s_c_iter cstart() const { return m_start; }


    template <typename String, typename Translator> inline
    string_path<String, Translator>::string_path(char_type separator)
        : m_separator(separator), m_start(m_value.begin())
    {}


    template <typename String, typename Translator> inline
    string_path<String, Translator>::string_path(const String &value,
                                                 char_type separator,
                                                 Translator tr)
        : m_value(value), m_separator(separator),
          m_tr(tr), m_start(m_value.begin())
    {}


    template <typename String, typename Translator> inline
    string_path<String, Translator>::string_path(const char_type *value,
                                                 char_type separator,
                                                 Translator tr)
        : m_value(value), m_separator(separator),
          m_tr(tr), m_start(m_value.begin())
    {}


    template <typename String, typename Translator> inline
    string_path<String, Translator>::string_path(const string_path &o)
        : m_value(o.m_value), m_separator(o.m_separator),
          m_tr(o.m_tr), m_start(m_value.begin())
    {
        std::advance(m_start, std::distance(o.m_value.begin(), o.cstart()));
    }


    template <typename String, typename Translator> inline
    string_path<String, Translator>&
    string_path<String, Translator>::operator =(const string_path &o)
    {
        m_value = o.m_value;
        m_separator = o.m_separator;
        m_tr = o.m_tr;
        m_start = m_value.begin();
        std::advance(m_start, std::distance(o.m_value.begin(), o.cstart()));
        return *this;
    }


    template <typename String, typename Translator>
    typename Translator::external_type string_path<String, Translator>::reduce()
    {
        BOOST_ASSERT(!empty() && "Reducing empty path");

        s_iter next_sep = std::find(m_start, m_value.end(), m_separator);
        String part(m_start, next_sep);
        m_start = next_sep;
        if(!empty()) {
          // Unless we're at the end, skip the separator we found.
          ++m_start;
        }

        if(optional<key_type> key = m_tr.get_value(part)) {
            return *key;
        }
        BOOST_PROPERTY_TREE_THROW(ptree_bad_path("Path syntax error", *this));
    }


    template <typename String, typename Translator> inline
    bool string_path<String, Translator>::empty() const
    {
        return m_start == m_value.end();
    }


    template <typename String, typename Translator> inline
    bool string_path<String, Translator>::single() const
    {
        return std::find(static_cast<s_c_iter>(m_start),
                         m_value.end(), m_separator)
            == m_value.end();
    }


    template <typename String, typename Translator> inline
    string_path<String, Translator> operator /(
                                  string_path<String, Translator> p1,
                                  const string_path<String, Translator> &p2)
    {
        p1 /= p2;
        return p1;
    }

    template <typename String, typename Translator> inline
    string_path<String, Translator> operator /(
                                  string_path<String, Translator> p1,
                                  const typename String::value_type *p2)
    {
        p1 /= p2;
        return p1;
    }


    template <typename String, typename Translator> inline
    string_path<String, Translator> operator /(
                                  const typename String::value_type *p1,
                                  const string_path<String, Translator> &p2)
    {
        string_path<String, Translator> t(p1);
        t /= p2;
        return t;
    }

    template<class Archive, class K, class D, class C>
    inline void save(Archive &ar,
                     const basic_ptree<K, D, C> &t,
                     const unsigned int file_version)
    {
        using namespace boost::serialization;
        stl::save_collection<Archive, basic_ptree<K, D, C> >(ar, t);
        ar << make_nvp("data", t.data());
    }

    template<class Archive, class K, class D, class C>
    inline void load(Archive &ar,
                     basic_ptree<K, D, C> &t,
                     const unsigned int file_version)
    {
        using namespace boost::serialization;
        // Load children
        stl::load_collection<Archive,
                             basic_ptree<K, D, C>,
                             stl::archive_input_seq<Archive,
                                 basic_ptree<K, D, C> >,
                             stl::no_reserve_imp<
                                 basic_ptree<K, D, C> >
                            >(ar, t);

        // Load data (must be after load_collection, as it calls clear())
        ar >> make_nvp("data", t.data());
    }

    template<class Archive, class K, class D, class C>
    inline void serialize(Archive &ar,
                          basic_ptree<K, D, C> &t,
                          const unsigned int file_version)
    {
        using namespace boost::serialization;
        split_free(ar, t, file_version);
    }

        xml_parser_error(const std::string &msg,
                         const std::string &file,
                         unsigned long l):
            file_parser_error(msg, file, l)
        {
        }

        file_parser_error(const std::string &msg,
                          const std::string &file,
                          unsigned long l) :
            ptree_error(format_what(msg, file, l)),
            m_message(msg), m_filename(file), m_line(l)
        {
        }


        ~file_parser_error() throw()
            // gcc 3.4.2 complains about lack of throw specifier on compiler
            // generated dtor
        {
        }

        std::string message() const
        {
            return m_message;
        }

        std::string filename() const
        {
            return m_filename;
        }

        unsigned long line() const
        {
            return m_line;
        }

        static std::string format_what(const std::string &msg,
                                       const std::string &file,
                                       unsigned long l)
        {
            std::stringstream stream;
            stream << (file.empty() ? "<unspecified file>" : file.c_str());
            if (l > 0)
                stream << '(' << l << ')';
            stream << ": " << msg;
            return stream.str();
        }

            a_object_s(context &c): c(c) { }

            void operator()(Ch) const
            {
                if (c.stack.empty())
                    c.stack.push_back(&c.root);
                else
                {
                    Ptree *parent = c.stack.back();
                    Ptree *child = &parent->push_back(std::make_pair(c.name, Ptree()))->second;
                    c.stack.push_back(child);
                    c.name.clear();
                }
            }

            a_object_e(context &c): c(c) { }

            void operator()(Ch) const
            {
                BOOST_ASSERT(c.stack.size() >= 1);
                c.stack.pop_back();
            }

            a_name(context &c): c(c) { }

            void operator()(It, It) const
            {
                c.name.swap(c.string);
                c.string.clear();
            }

            a_string_val(context &c): c(c) { }

            void operator()(It, It) const
            {
                BOOST_ASSERT(c.stack.size() >= 1);
                c.stack.back()->push_back(std::make_pair(c.name, Ptree(c.string)));
                c.name.clear();
                c.string.clear();
            }

            a_literal_val(context &c): c(c) { }

            void operator()(It b, It e) const
            {
                BOOST_ASSERT(c.stack.size() >= 1);
                c.stack.back()->push_back(std::make_pair(c.name,
                    Ptree(Str(b, e))));
                c.name.clear();
                c.string.clear();
            }

            a_char(context &c): c(c) { }

            void operator()(It b, It e) const
            {
                c.string += *b;
            }

            a_escape(context &c): c(c) { }

            void operator()(Ch ch) const
            {
                switch (ch)
                {
                    case Ch('\"'): c.string += Ch('\"'); break;
                    case Ch('\\'): c.string += Ch('\\'); break;
                    case Ch('/'): c.string += Ch('/'); break;
                    case Ch('b'): c.string += Ch('\b'); break;
                    case Ch('f'): c.string += Ch('\f'); break;
                    case Ch('n'): c.string += Ch('\n'); break;
                    case Ch('r'): c.string += Ch('\r'); break;
                    case Ch('t'): c.string += Ch('\t'); break;
                    default: BOOST_ASSERT(0);
                }
            }

            a_unicode(context &c): c(c) { }

            void operator()(unsigned long u) const
            {
                u = (std::min)(u, static_cast<unsigned long>((std::numeric_limits<Ch>::max)()));
                c.string += Ch(u);
            }


            definition(const json_grammar &self)
            {

                using namespace boost::spirit::classic;
                // There's a boost::assertion too, so another explicit using
                // here:
                using boost::spirit::classic::assertion;

                // Assertions
                assertion<std::string> expect_root("expected object or array");
                assertion<std::string> expect_eoi("expected end of input");
                assertion<std::string> expect_objclose("expected ',' or '}'");
                assertion<std::string> expect_arrclose("expected ',' or ']'");
                assertion<std::string> expect_name("expected object name");
                assertion<std::string> expect_colon("expected ':'");
                assertion<std::string> expect_value("expected value");
                assertion<std::string> expect_escape("invalid escape sequence");

                // JSON grammar rules
                root 
                    =   expect_root(object | array) 
                        >> expect_eoi(end_p)
                        ;
                
                object 
                    =   ch_p('{')[typename Context::a_object_s(self.c)]
                        >> (ch_p('}')[typename Context::a_object_e(self.c)] 
                           | (list_p(member, ch_p(','))
                              >> expect_objclose(ch_p('}')[typename Context::a_object_e(self.c)])
                             )
                           )
                        ;
                
                member 
                    =   expect_name(string[typename Context::a_name(self.c)]) 
                        >> expect_colon(ch_p(':')) 
                        >> expect_value(value)
                        ;
                
                array 
                    =   ch_p('[')[typename Context::a_object_s(self.c)]
                        >> (ch_p(']')[typename Context::a_object_e(self.c)] 
                            | (list_p(item, ch_p(','))
                               >> expect_arrclose(ch_p(']')[typename Context::a_object_e(self.c)])
                              )
                           )
                    ;

                item 
                    =   expect_value(value)
                        ;

                value 
                    =   string[typename Context::a_string_val(self.c)] 
                        | (number | str_p("true") | "false" | "null")[typename Context::a_literal_val(self.c)]
                        | object 
                        | array
                        ;
                
                number 
                    =   !ch_p("-") >>
                        (ch_p("0") | (range_p(Ch('1'), Ch('9')) >> *digit_p)) >>
                        !(ch_p(".") >> +digit_p) >>
                        !(chset_p(detail::widen<Ch>("eE").c_str()) >>
                          !chset_p(detail::widen<Ch>("-+").c_str()) >>
                          +digit_p)
                        ;

                string
                    =   +(lexeme_d[confix_p('\"', *character, '\"')])
                        ;

                character
                    =   (anychar_p - "\\" - "\"")
                            [typename Context::a_char(self.c)]
                    |   ch_p("\\") >> expect_escape(escape)
                    ;

                escape
                    =   chset_p(detail::widen<Ch>("\"\\/bfnrt").c_str())
                            [typename Context::a_escape(self.c)]
                    |   'u' >> uint_parser<unsigned long, 16, 4, 4>()
                            [typename Context::a_unicode(self.c)]
                    ;

                // Debug
                BOOST_SPIRIT_DEBUG_RULE(root);
                BOOST_SPIRIT_DEBUG_RULE(object);
                BOOST_SPIRIT_DEBUG_RULE(member);
                BOOST_SPIRIT_DEBUG_RULE(array);
                BOOST_SPIRIT_DEBUG_RULE(item);
                BOOST_SPIRIT_DEBUG_RULE(value);
                BOOST_SPIRIT_DEBUG_RULE(string);
                BOOST_SPIRIT_DEBUG_RULE(number);
                BOOST_SPIRIT_DEBUG_RULE(escape);
                BOOST_SPIRIT_DEBUG_RULE(character);

            }


    template<class It, class Ch>
    unsigned long count_lines(It begin, It end)
    {
        return static_cast<unsigned long>(std::count(begin, end, Ch('\n')) + 1);
    }

        parse_error(const char *wa, void *we)
            : m_what(wa)
            , m_where(we)
        {
        }

        virtual const char *what() const throw()
        {
            return m_what;
        }

        template<class Ch>
        Ch *where() const
        {
            return reinterpret_cast<Ch *>(m_where);
        }

        template<class Ch>
        inline std::size_t measure(const Ch *p)
        {
            const Ch *tmp = p;
            while (*tmp) 
                ++tmp;
            return tmp - p;
        }

        template<class Ch>
        inline bool compare(const Ch *p1, std::size_t size1, const Ch *p2, std::size_t size2, bool case_sensitive)
        {
            if (size1 != size2)
                return false;
            if (case_sensitive)
            {
                for (const Ch *end = p1 + size1; p1 < end; ++p1, ++p2)
                    if (*p1 != *p2)
                        return false;
            }
            else
            {
                for (const Ch *end = p1 + size1; p1 < end; ++p1, ++p2)
                    if (lookup_tables<0>::lookup_upcase[static_cast<unsigned char>(*p1)] != lookup_tables<0>::lookup_upcase[static_cast<unsigned char>(*p2)])
                        return false;
            }
            return true;
        }


        template<class Ch>
        inline size_t get_index(const Ch c)
        {
            // If not ASCII char, its semantic is same as plain 'z'.
            // char could be signed, so first stretch and make unsigned.
            unsigned n = c;
            if (n > 127)
            {
                return 'z';
            }
            return c;
        }

        memory_pool()
            : m_alloc_func(0)
            , m_free_func(0)
        {
            init();
        }

        ~memory_pool()
        {
            clear();
        }

        xml_node<Ch> *allocate_node(node_type type, 
                                    const Ch *name = 0, const Ch *value = 0, 
                                    std::size_t name_size = 0, std::size_t value_size = 0)
        {
            void *memory = allocate_aligned(sizeof(xml_node<Ch>));
            xml_node<Ch> *node = new(memory) xml_node<Ch>(type);
            if (name)
            {
                if (name_size > 0)
                    node->name(name, name_size);
                else
                    node->name(name);
            }
            if (value)
            {
                if (value_size > 0)
                    node->value(value, value_size);
                else
                    node->value(value);
            }
            return node;
        }

        xml_attribute<Ch> *allocate_attribute(const Ch *name = 0, const Ch *value = 0, 
                                              std::size_t name_size = 0, std::size_t value_size = 0)
        {
            void *memory = allocate_aligned(sizeof(xml_attribute<Ch>));
            xml_attribute<Ch> *attribute = new(memory) xml_attribute<Ch>;
            if (name)
            {
                if (name_size > 0)
                    attribute->name(name, name_size);
                else
                    attribute->name(name);
            }
            if (value)
            {
                if (value_size > 0)
                    attribute->value(value, value_size);
                else
                    attribute->value(value);
            }
            return attribute;
        }

        Ch *allocate_string(const Ch *source = 0, std::size_t size = 0)
        {
            BOOST_ASSERT(source || size);     // Either source or size (or both) must be specified
            if (size == 0)
                size = internal::measure(source) + 1;
            Ch *result = static_cast<Ch *>(allocate_aligned(size * sizeof(Ch)));
            if (source)
                for (std::size_t i = 0; i < size; ++i)
                    result[i] = source[i];
            return result;
        }

        xml_node<Ch> *clone_node(const xml_node<Ch> *source, xml_node<Ch> *result = 0)
        {
            // Prepare result node
            if (result)
            {
                result->remove_all_attributes();
                result->remove_all_nodes();
                result->type(source->type());
            }
            else
                result = allocate_node(source->type());

            // Clone name and value
            result->name(source->name(), source->name_size());
            result->value(source->value(), source->value_size());

            // Clone child nodes and attributes
            for (xml_node<Ch> *child = source->first_node(); child; child = child->next_sibling())
                result->append_node(clone_node(child));
            for (xml_attribute<Ch> *attr = source->first_attribute(); attr; attr = attr->next_attribute())
                result->append_attribute(allocate_attribute(attr->name(), attr->value(), attr->name_size(), attr->value_size()));

            return result;
        }

        void clear()
        {
            while (m_begin != m_static_memory)
            {
                char *previous_begin = reinterpret_cast<header *>(align(m_begin))->previous_begin;
                if (m_free_func)
                    m_free_func(m_begin);
                else
                    delete[] m_begin;
                m_begin = previous_begin;
            }
            init();
        }

        void set_allocator(boost_ptree_raw_alloc_func *af, boost_ptree_raw_free_func *ff)
        {
            BOOST_ASSERT(m_begin == m_static_memory && m_ptr == align(m_begin));    // Verify that no memory is allocated yet
            m_alloc_func = af;
            m_free_func = ff;
        }


        void init()
        {
            m_begin = m_static_memory;
            m_ptr = align(m_begin);
            m_end = m_static_memory + sizeof(m_static_memory);
        }

        
        char *align(char *ptr)
        {
            std::size_t alignment = ((BOOST_PROPERTY_TREE_RAPIDXML_ALIGNMENT - (std::size_t(ptr) & (BOOST_PROPERTY_TREE_RAPIDXML_ALIGNMENT - 1))) & (BOOST_PROPERTY_TREE_RAPIDXML_ALIGNMENT - 1));
            return ptr + alignment;
        }

        
        char *allocate_raw(std::size_t size)
        {
            // Allocate
            void *memory;   
            if (m_alloc_func)   // Allocate memory using either user-specified allocation function or global operator new[]
            {
                memory = m_alloc_func(size);
                BOOST_ASSERT(memory); // Allocator is not allowed to return 0, on failure it must either throw, stop the program or use longjmp
            }
            else
            {
                memory = new char[size];
            }
            return static_cast<char *>(memory);
        }

        
        void *allocate_aligned(std::size_t size)
        {
            // Calculate aligned pointer
            char *result = align(m_ptr);

            // If not enough memory left in current pool, allocate a new pool
            if (result + size > m_end)
            {
                // Calculate required pool size (may be bigger than BOOST_PROPERTY_TREE_RAPIDXML_DYNAMIC_POOL_SIZE)
                std::size_t pool_size = BOOST_PROPERTY_TREE_RAPIDXML_DYNAMIC_POOL_SIZE;
                if (pool_size < size)
                    pool_size = size;
                
                // Allocate
                std::size_t alloc_size = sizeof(header) + (2 * BOOST_PROPERTY_TREE_RAPIDXML_ALIGNMENT - 2) + pool_size;     // 2 alignments required in worst case: one for header, one for actual allocation
                char *raw_memory = allocate_raw(alloc_size);
                    
                // Setup new pool in allocated memory
                char *pool = align(raw_memory);
                header *new_header = reinterpret_cast<header *>(pool);
                new_header->previous_begin = m_begin;
                m_begin = raw_memory;
                m_ptr = pool + sizeof(header);
                m_end = raw_memory + alloc_size;

                // Calculate aligned pointer again using new pool
                result = align(m_ptr);
            }

            // Update pool and return aligned pointer
            m_ptr = result + size;
            return result;
        }

        xml_base()
            : m_name(0)
            , m_value(0)
            , m_parent(0)
        {
        }

        Ch *name() const
        {
            return m_name ? m_name : nullstr();
        }

        std::size_t name_size() const
        {
            return m_name ? m_name_size : 0;
        }

        Ch *value() const
        {
            return m_value ? m_value : nullstr();
        }

        std::size_t value_size() const
        {
            return m_value ? m_value_size : 0;
        }

        void name(const Ch *n)
        {
            name(n, internal::measure(n));
        }

        void value(const Ch *val)
        {
            this->value(val, internal::measure(val));
        }

        xml_node<Ch> *parent() const
        {
            return m_parent;
        }

        static Ch *nullstr()
        {
            static Ch zero = Ch('\0');
            return &zero;
        }

        xml_attribute()
        {
        }

        xml_document<Ch> *document() const
        {
            if (xml_node<Ch> *node = this->parent())
            {
                while (node->parent())
                    node = node->parent();
                return node->type() == node_document ? static_cast<xml_document<Ch> *>(node) : 0;
            }
            else
                return 0;
        }

        xml_attribute<Ch> *previous_attribute(const Ch *n = 0, std::size_t nsize = 0, bool case_sensitive = true) const
        {
            if (n)
            {
                if (nsize == 0)
                    nsize = internal::measure(n);
                for (xml_attribute<Ch> *attribute = m_prev_attribute; attribute; attribute = attribute->m_prev_attribute)
                    if (internal::compare(attribute->name(), attribute->name_size(), n, nsize, case_sensitive))
                        return attribute;
                return 0;
            }
            else
                return this->m_parent ? m_prev_attribute : 0;
        }

        xml_attribute<Ch> *next_attribute(const Ch *n = 0, std::size_t nsize = 0, bool case_sensitive = true) const
        {
            if (n)
            {
                if (nsize == 0)
                    nsize = internal::measure(n);
                for (xml_attribute<Ch> *attribute = m_next_attribute; attribute; attribute = attribute->m_next_attribute)
                    if (internal::compare(attribute->name(), attribute->name_size(), n, nsize, case_sensitive))
                        return attribute;
                return 0;
            }
            else
                return this->m_parent ? m_next_attribute : 0;
        }

        xml_node(node_type t)
            : m_type(t)
            , m_first_node(0)
            , m_first_attribute(0)
        {
        }

        node_type type() const
        {
            return m_type;
        }

        xml_document<Ch> *document() const
        {
            xml_node<Ch> *node = const_cast<xml_node<Ch> *>(this);
            while (node->parent())
                node = node->parent();
            return node->type() == node_document ? static_cast<xml_document<Ch> *>(node) : 0;
        }

        xml_node<Ch> *first_node(const Ch *n = 0, std::size_t nsize = 0, bool case_sensitive = true) const
        {
            if (n)
            {
                if (nsize == 0)
                    nsize = internal::measure(n);
                for (xml_node<Ch> *child = m_first_node; child; child = child->next_sibling())
                    if (internal::compare(child->name(), child->name_size(), n, nsize, case_sensitive))
                        return child;
                return 0;
            }
            else
                return m_first_node;
        }

        xml_node<Ch> *last_node(const Ch *n = 0, std::size_t nsize = 0, bool case_sensitive = true) const
        {
            BOOST_ASSERT(m_first_node);  // Cannot query for last child if node has no children
            if (n)
            {
                if (nsize == 0)
                    nsize = internal::measure(n);
                for (xml_node<Ch> *child = m_last_node; child; child = child->previous_sibling())
                    if (internal::compare(child->name(), child->name_size(), n, nsize, case_sensitive))
                        return child;
                return 0;
            }
            else
                return m_last_node;
        }

        xml_node<Ch> *previous_sibling(const Ch *n = 0, std::size_t nsize = 0, bool case_sensitive = true) const
        {
            BOOST_ASSERT(this->m_parent);     // Cannot query for siblings if node has no parent
            if (n)
            {
                if (nsize == 0)
                    nsize = internal::measure(n);
                for (xml_node<Ch> *sibling = m_prev_sibling; sibling; sibling = sibling->m_prev_sibling)
                    if (internal::compare(sibling->name(), sibling->name_size(), n, nsize, case_sensitive))
                        return sibling;
                return 0;
            }
            else
                return m_prev_sibling;
        }

        xml_node<Ch> *next_sibling(const Ch *n = 0, std::size_t nsize = 0, bool case_sensitive = true) const
        {
            BOOST_ASSERT(this->m_parent);     // Cannot query for siblings if node has no parent
            if (n)
            {
                if (nsize == 0)
                    nsize = internal::measure(n);
                for (xml_node<Ch> *sibling = m_next_sibling; sibling; sibling = sibling->m_next_sibling)
                    if (internal::compare(sibling->name(), sibling->name_size(), n, nsize, case_sensitive))
                        return sibling;
                return 0;
            }
            else
                return m_next_sibling;
        }

        xml_attribute<Ch> *first_attribute(const Ch *n = 0, std::size_t nsize = 0, bool case_sensitive = true) const
        {
            if (n)
            {
                if (nsize == 0)
                    nsize = internal::measure(n);
                for (xml_attribute<Ch> *attribute = m_first_attribute; attribute; attribute = attribute->m_next_attribute)
                    if (internal::compare(attribute->name(), attribute->name_size(), n, nsize, case_sensitive))
                        return attribute;
                return 0;
            }
            else
                return m_first_attribute;
        }

        xml_attribute<Ch> *last_attribute(const Ch *n = 0, std::size_t nsize = 0, bool case_sensitive = true) const
        {
            if (n)
            {
                if (nsize == 0)
                    nsize = internal::measure(n);
                for (xml_attribute<Ch> *attribute = m_last_attribute; attribute; attribute = attribute->m_prev_attribute)
                    if (internal::compare(attribute->name(), attribute->name_size(), n, nsize, case_sensitive))
                        return attribute;
                return 0;
            }
            else
                return m_first_attribute ? m_last_attribute : 0;
        }

        void type(node_type t)
        {
            m_type = t;
        }

        void prepend_node(xml_node<Ch> *child)
        {
            BOOST_ASSERT(child && !child->parent() && child->type() != node_document);
            if (first_node())
            {
                child->m_next_sibling = m_first_node;
                m_first_node->m_prev_sibling = child;
            }
            else
            {
                child->m_next_sibling = 0;
                m_last_node = child;
            }
            m_first_node = child;
            child->m_parent = this;
            child->m_prev_sibling = 0;
        }

        void append_node(xml_node<Ch> *child)
        {
            BOOST_ASSERT(child && !child->parent() && child->type() != node_document);
            if (first_node())
            {
                child->m_prev_sibling = m_last_node;
                m_last_node->m_next_sibling = child;
            }
            else
            {
                child->m_prev_sibling = 0;
                m_first_node = child;
            }
            m_last_node = child;
            child->m_parent = this;
            child->m_next_sibling = 0;
        }

        void insert_node(xml_node<Ch> *where, xml_node<Ch> *child)
        {
            BOOST_ASSERT(!where || where->parent() == this);
            BOOST_ASSERT(child && !child->parent() && child->type() != node_document);
            if (where == m_first_node)
                prepend_node(child);
            else if (where == 0)
                append_node(child);
            else
            {
                child->m_prev_sibling = where->m_prev_sibling;
                child->m_next_sibling = where;
                where->m_prev_sibling->m_next_sibling = child;
                where->m_prev_sibling = child;
                child->m_parent = this;
            }
        }

        void remove_first_node()
        {
            BOOST_ASSERT(first_node());
            xml_node<Ch> *child = m_first_node;
            m_first_node = child->m_next_sibling;
            if (child->m_next_sibling)
                child->m_next_sibling->m_prev_sibling = 0;
            else
                m_last_node = 0;
            child->m_parent = 0;
        }

        void remove_last_node()
        {
            BOOST_ASSERT(first_node());
            xml_node<Ch> *child = m_last_node;
            if (child->m_prev_sibling)
            {
                m_last_node = child->m_prev_sibling;
                child->m_prev_sibling->m_next_sibling = 0;
            }
            else
                m_first_node = 0;
            child->m_parent = 0;
        }

        void remove_node(xml_node<Ch> *where)
        {
            BOOST_ASSERT(where && where->parent() == this);
            BOOST_ASSERT(first_node());
            if (where == m_first_node)
                remove_first_node();
            else if (where == m_last_node)
                remove_last_node();
            else
            {
                where->m_prev_sibling->m_next_sibling = where->m_next_sibling;
                where->m_next_sibling->m_prev_sibling = where->m_prev_sibling;
                where->m_parent = 0;
            }
        }

        void remove_all_nodes()
        {
            for (xml_node<Ch> *node = first_node(); node; node = node->m_next_sibling)
                node->m_parent = 0;
            m_first_node = 0;
        }

        void prepend_attribute(xml_attribute<Ch> *attribute)
        {
            BOOST_ASSERT(attribute && !attribute->parent());
            if (first_attribute())
            {
                attribute->m_next_attribute = m_first_attribute;
                m_first_attribute->m_prev_attribute = attribute;
            }
            else
            {
                attribute->m_next_attribute = 0;
                m_last_attribute = attribute;
            }
            m_first_attribute = attribute;
            attribute->m_parent = this;
            attribute->m_prev_attribute = 0;
        }

        void append_attribute(xml_attribute<Ch> *attribute)
        {
            BOOST_ASSERT(attribute && !attribute->parent());
            if (first_attribute())
            {
                attribute->m_prev_attribute = m_last_attribute;
                m_last_attribute->m_next_attribute = attribute;
            }
            else
            {
                attribute->m_prev_attribute = 0;
                m_first_attribute = attribute;
            }
            m_last_attribute = attribute;
            attribute->m_parent = this;
            attribute->m_next_attribute = 0;
        }

        void insert_attribute(xml_attribute<Ch> *where, xml_attribute<Ch> *attribute)
        {
            BOOST_ASSERT(!where || where->parent() == this);
            BOOST_ASSERT(attribute && !attribute->parent());
            if (where == m_first_attribute)
                prepend_attribute(attribute);
            else if (where == 0)
                append_attribute(attribute);
            else
            {
                attribute->m_prev_attribute = where->m_prev_attribute;
                attribute->m_next_attribute = where;
                where->m_prev_attribute->m_next_attribute = attribute;
                where->m_prev_attribute = attribute;
                attribute->m_parent = this;
            }
        }

        void remove_first_attribute()
        {
            BOOST_ASSERT(first_attribute());
            xml_attribute<Ch> *attribute = m_first_attribute;
            if (attribute->m_next_attribute)
            {
                attribute->m_next_attribute->m_prev_attribute = 0;
            }
            else
                m_last_attribute = 0;
            attribute->m_parent = 0;
            m_first_attribute = attribute->m_next_attribute;
        }

        void remove_last_attribute()
        {
            BOOST_ASSERT(first_attribute());
            xml_attribute<Ch> *attribute = m_last_attribute;
            if (attribute->m_prev_attribute)
            {
                attribute->m_prev_attribute->m_next_attribute = 0;
                m_last_attribute = attribute->m_prev_attribute;
            }
            else
                m_first_attribute = 0;
            attribute->m_parent = 0;
        }

        void remove_attribute(xml_attribute<Ch> *where)
        {
            BOOST_ASSERT(first_attribute() && where->parent() == this);
            if (where == m_first_attribute)
                remove_first_attribute();
            else if (where == m_last_attribute)
                remove_last_attribute();
            else
            {
                where->m_prev_attribute->m_next_attribute = where->m_next_attribute;
                where->m_next_attribute->m_prev_attribute = where->m_prev_attribute;
                where->m_parent = 0;
            }
        }

        void remove_all_attributes()
        {
            for (xml_attribute<Ch> *attribute = first_attribute(); attribute; attribute = attribute->m_next_attribute)
                attribute->m_parent = 0;
            m_first_attribute = 0;
        }

        xml_document()
            : xml_node<Ch>(node_document)
        {
        }

        template<int Flags>
        void parse(Ch *text)
        {
            BOOST_ASSERT(text);
            
            // Remove current contents
            this->remove_all_nodes();
            this->remove_all_attributes();
            
            // Parse BOM, if any
            parse_bom<Flags>(text);
            
            // Parse children
            while (1)
            {
                // Skip whitespace before node
                skip<whitespace_pred, Flags>(text);
                if (*text == 0)
                    break;

                // Parse and append new child
                if (*text == Ch('<'))
                {
                    ++text;     // Skip '<'
                    if (xml_node<Ch> *node = parse_node<Flags>(text))
                        this->append_node(node);
                }
                else
                    BOOST_PROPERTY_TREE_RAPIDXML_PARSE_ERROR("expected <", text);
            }

        }

        void clear()
        {
            this->remove_all_nodes();
            this->remove_all_attributes();
            memory_pool<Ch>::clear();
        }

            static unsigned char test(Ch ch)
            {
                return internal::lookup_tables<0>::lookup_whitespace[internal::get_index(ch)];
            }

            static unsigned char test(Ch ch)
            {
                return internal::lookup_tables<0>::lookup_node_name[internal::get_index(ch)];
            }

            static unsigned char test(Ch ch)
            {
                return internal::lookup_tables<0>::lookup_attribute_name[internal::get_index(ch)];
            }

            static unsigned char test(Ch ch)
            {
                return internal::lookup_tables<0>::lookup_text[internal::get_index(ch)];
            }

            static unsigned char test(Ch ch)
            {
                return internal::lookup_tables<0>::lookup_text_pure_no_ws[internal::get_index(ch)];
            }

            static unsigned char test(Ch ch)
            {
                return internal::lookup_tables<0>::lookup_text_pure_with_ws[internal::get_index(ch)];
            }

            static unsigned char test(Ch ch)
            {
                if (Quote == Ch('\''))
                    return internal::lookup_tables<0>::lookup_attribute_data_1[internal::get_index(ch)];
                if (Quote == Ch('\"'))
                    return internal::lookup_tables<0>::lookup_attribute_data_2[internal::get_index(ch)];
                return 0;       // Should never be executed, to avoid warnings on Comeau
            }

            static unsigned char test(Ch ch)
            {
                if (Quote == Ch('\''))
                    return internal::lookup_tables<0>::lookup_attribute_data_1_pure[internal::get_index(ch)];
                if (Quote == Ch('\"'))
                    return internal::lookup_tables<0>::lookup_attribute_data_2_pure[internal::get_index(ch)];
                return 0;       // Should never be executed, to avoid warnings on Comeau
            }

        template<int Flags>
        static void insert_coded_character(Ch *&text, unsigned long code)
        {
            if (Flags & parse_no_utf8)
            {
                // Insert 8-bit ASCII character
                // Todo: possibly verify that code is less than 256 and use replacement char otherwise?
                text[0] = static_cast<unsigned char>(code);
                text += 1;
            }
            else
            {
                // Insert UTF8 sequence
                if (code < 0x80)    // 1 byte sequence
                {
                    text[0] = static_cast<unsigned char>(code);
                    text += 1;
                }
                else if (code < 0x800)  // 2 byte sequence
                {
                    text[1] = static_cast<unsigned char>((code | 0x80) & 0xBF); code >>= 6;
                    text[0] = static_cast<unsigned char>(code | 0xC0);
                    text += 2;
                }
                else if (code < 0x10000)    // 3 byte sequence
                {
                    text[2] = static_cast<unsigned char>((code | 0x80) & 0xBF); code >>= 6;
                    text[1] = static_cast<unsigned char>((code | 0x80) & 0xBF); code >>= 6;
                    text[0] = static_cast<unsigned char>(code | 0xE0);
                    text += 3;
                }
                else if (code < 0x110000)   // 4 byte sequence
                {
                    text[3] = static_cast<unsigned char>((code | 0x80) & 0xBF); code >>= 6;
                    text[2] = static_cast<unsigned char>((code | 0x80) & 0xBF); code >>= 6;
                    text[1] = static_cast<unsigned char>((code | 0x80) & 0xBF); code >>= 6;
                    text[0] = static_cast<unsigned char>(code | 0xF0);
                    text += 4;
                }
                else    // Invalid, only codes up to 0x10FFFF are allowed in Unicode
                {
                    BOOST_PROPERTY_TREE_RAPIDXML_PARSE_ERROR("invalid numeric character entity", text);
                }
            }
        }

        template<class StopPred, int Flags>
        static void skip(Ch *&text)
        {
            Ch *tmp = text;
            while (StopPred::test(*tmp))
                ++tmp;
            text = tmp;
        }

        template<class StopPred, class StopPredPure, int Flags>
        static Ch *skip_and_expand_character_refs(Ch *&text)
        {
            // If entity translation, whitespace condense and whitespace trimming is disabled, use plain skip
            if (Flags & parse_no_entity_translation && 
                !(Flags & parse_normalize_whitespace) &&
                !(Flags & parse_trim_whitespace))
            {
                skip<StopPred, Flags>(text);
                return text;
            }
            
            // Use simple skip until first modification is detected
            skip<StopPredPure, Flags>(text);

            // Use translation skip
            Ch *src = text;
            Ch *dest = src;
            while (StopPred::test(*src))
            {
                // If entity translation is enabled    
                if (!(Flags & parse_no_entity_translation))
                {
                    // Test if replacement is needed
                    if (src[0] == Ch('&'))
                    {
                        switch (src[1])
                        {

                        // &amp; &apos;
                        case Ch('a'): 
                            if (src[2] == Ch('m') && src[3] == Ch('p') && src[4] == Ch(';'))
                            {
                                *dest = Ch('&');
                                ++dest;
                                src += 5;
                                continue;
                            }
                            if (src[2] == Ch('p') && src[3] == Ch('o') && src[4] == Ch('s') && src[5] == Ch(';'))
                            {
                                *dest = Ch('\'');
                                ++dest;
                                src += 6;
                                continue;
                            }
                            break;

                        // &quot;
                        case Ch('q'): 
                            if (src[2] == Ch('u') && src[3] == Ch('o') && src[4] == Ch('t') && src[5] == Ch(';'))
                            {
                                *dest = Ch('"');
                                ++dest;
                                src += 6;
                                continue;
                            }
                            break;

                        // &gt;
                        case Ch('g'): 
                            if (src[2] == Ch('t') && src[3] == Ch(';'))
                            {
                                *dest = Ch('>');
                                ++dest;
                                src += 4;
                                continue;
                            }
                            break;

                        // &lt;
                        case Ch('l'): 
                            if (src[2] == Ch('t') && src[3] == Ch(';'))
                            {
                                *dest = Ch('<');
                                ++dest;
                                src += 4;
                                continue;
                            }
                            break;

                        // &#...; - assumes ASCII
                        case Ch('#'): 
                            if (src[2] == Ch('x'))
                            {
                                unsigned long code = 0;
                                src += 3;   // Skip &#x
                                while (1)
                                {
                                    unsigned char digit = internal::lookup_tables<0>::lookup_digits[static_cast<unsigned char>(*src)];
                                    if (digit == 0xFF)
                                        break;
                                    code = code * 16 + digit;
                                    ++src;
                                }
                                insert_coded_character<Flags>(dest, code);    // Put character in output
                            }
                            else
                            {
                                unsigned long code = 0;
                                src += 2;   // Skip &#
                                while (1)
                                {
                                    unsigned char digit = internal::lookup_tables<0>::lookup_digits[static_cast<unsigned char>(*src)];
                                    if (digit == 0xFF)
                                        break;
                                    code = code * 10 + digit;
                                    ++src;
                                }
                                insert_coded_character<Flags>(dest, code);    // Put character in output
                            }
                            if (*src == Ch(';'))
                                ++src;
                            else
                                BOOST_PROPERTY_TREE_RAPIDXML_PARSE_ERROR("expected ;", src);
                            continue;

                        // Something else
                        default:
                            // Ignore, just copy '&' verbatim
                            break;

                        }
                    }
                }
                
                // If whitespace condensing is enabled
                if (Flags & parse_normalize_whitespace)
                {
                    // Test if condensing is needed                 
                    if (whitespace_pred::test(*src))
                    {
                        *dest = Ch(' '); ++dest;    // Put single space in dest
                        ++src;                      // Skip first whitespace char
                        // Skip remaining whitespace chars
                        while (whitespace_pred::test(*src))
                            ++src;
                        continue;
                    }
                }

                // No replacement, only copy character
                *dest++ = *src++;

            }

            // Return new end
            text = src;
            return dest;

        }

        template<int Flags>
        void parse_bom(char *&text)
        {
            if (static_cast<unsigned char>(text[0]) == 0xEF && 
                static_cast<unsigned char>(text[1]) == 0xBB && 
                static_cast<unsigned char>(text[2]) == 0xBF)
            {
                text += 3;
            }
        }

        template<int Flags>
        void parse_bom(wchar_t *&text)
        {
            const wchar_t bom = 0xFEFF;
            if (text[0] == bom)
            {
                ++text;
            }
        }

        template<int Flags>
        xml_node<Ch> *parse_xml_declaration(Ch *&text)
        {
            // If parsing of declaration is disabled
            if (!(Flags & parse_declaration_node))
            {
                // Skip until end of declaration
                while (text[0] != Ch('?') || text[1] != Ch('>'))
                {
                    if (!text[0])
                        BOOST_PROPERTY_TREE_RAPIDXML_PARSE_ERROR("unexpected end of data", text);
                    ++text;
                }
                text += 2;    // Skip '?>'
                return 0;
            }

            // Create declaration
            xml_node<Ch> *declaration = this->allocate_node(node_declaration);

            // Skip whitespace before attributes or ?>
            skip<whitespace_pred, Flags>(text);

            // Parse declaration attributes
            parse_node_attributes<Flags>(text, declaration);
            
            // Skip ?>
            if (text[0] != Ch('?') || text[1] != Ch('>'))
                BOOST_PROPERTY_TREE_RAPIDXML_PARSE_ERROR("expected ?>", text);
            text += 2;
            
            return declaration;
        }

        template<int Flags>
        xml_node<Ch> *parse_comment(Ch *&text)
        {
            // If parsing of comments is disabled
            if (!(Flags & parse_comment_nodes))
            {
                // Skip until end of comment
                while (text[0] != Ch('-') || text[1] != Ch('-') || text[2] != Ch('>'))
                {
                    if (!text[0])
                        BOOST_PROPERTY_TREE_RAPIDXML_PARSE_ERROR("unexpected end of data", text);
                    ++text;
                }
                text += 3;     // Skip '-->'
                return 0;      // Do not produce comment node
            }

            // Remember value start
            Ch *val = text;

            // Skip until end of comment
            while (text[0] != Ch('-') || text[1] != Ch('-') || text[2] != Ch('>'))
            {
                if (!text[0])
                    BOOST_PROPERTY_TREE_RAPIDXML_PARSE_ERROR("unexpected end of data", text);
                ++text;
            }

            // Create comment node
            xml_node<Ch> *comment = this->allocate_node(node_comment);
            comment->value(val, text - val);
            
            // Place zero terminator after comment value
            if (!(Flags & parse_no_string_terminators))
                *text = Ch('\0');
            
            text += 3;     // Skip '-->'
            return comment;
        }

        template<int Flags>
        xml_node<Ch> *parse_doctype(Ch *&text)
        {
            // Remember value start
            Ch *val = text;

            // Skip to >
            while (*text != Ch('>'))
            {
                // Determine character type
                switch (*text)
                {
                
                // If '[' encountered, scan for matching ending ']' using naive algorithm with depth
                // This works for all W3C test files except for 2 most wicked
                case Ch('['):
                {
                    ++text;     // Skip '['
                    int depth = 1;
                    while (depth > 0)
                    {
                        switch (*text)
                        {
                            case Ch('['): ++depth; break;
                            case Ch(']'): --depth; break;
                            case 0: BOOST_PROPERTY_TREE_RAPIDXML_PARSE_ERROR("unexpected end of data", text);
                            default: break;
                        }
                        ++text;
                    }
                    break;
                }
                
                // Error on end of text
                case Ch('\0'):
                    BOOST_PROPERTY_TREE_RAPIDXML_PARSE_ERROR("unexpected end of data", text);
                
                // Other character, skip it
                default:
                    ++text;

                }
            }
            
            // If DOCTYPE nodes enabled
            if (Flags & parse_doctype_node)
            {
                // Create a new doctype node
                xml_node<Ch> *doctype = this->allocate_node(node_doctype);
                doctype->value(val, text - val);
                
                // Place zero terminator after value
                if (!(Flags & parse_no_string_terminators))
                    *text = Ch('\0');

                text += 1;      // skip '>'
                return doctype;
            }
            else
            {
                text += 1;      // skip '>'
                return 0;
            }

        }

        template<int Flags>
        xml_node<Ch> *parse_pi(Ch *&text)
        {
            // If creation of PI nodes is enabled
            if (Flags & parse_pi_nodes)
            {
                // Create pi node
                xml_node<Ch> *pi = this->allocate_node(node_pi);

                // Extract PI target name
                Ch *n = text;
                skip<node_name_pred, Flags>(text);
                if (text == n)
                    BOOST_PROPERTY_TREE_RAPIDXML_PARSE_ERROR("expected PI target", text);
                pi->name(n, text - n);
                
                // Skip whitespace between pi target and pi
                skip<whitespace_pred, Flags>(text);

                // Remember start of pi
                Ch *val = text;
                
                // Skip to '?>'
                while (text[0] != Ch('?') || text[1] != Ch('>'))
                {
                    if (*text == Ch('\0'))
                        BOOST_PROPERTY_TREE_RAPIDXML_PARSE_ERROR("unexpected end of data", text);
                    ++text;
                }

                // Set pi value (verbatim, no entity expansion or whitespace normalization)
                pi->value(val, text - val);

                // Place zero terminator after name and value
                if (!(Flags & parse_no_string_terminators))
                {
                    pi->name()[pi->name_size()] = Ch('\0');
                    pi->value()[pi->value_size()] = Ch('\0');
                }
                
                text += 2;                          // Skip '?>'
                return pi;
            }
            else
            {
                // Skip to '?>'
                while (text[0] != Ch('?') || text[1] != Ch('>'))
                {
                    if (*text == Ch('\0'))
                        BOOST_PROPERTY_TREE_RAPIDXML_PARSE_ERROR("unexpected end of data", text);
                    ++text;
                }
                text += 2;    // Skip '?>'
                return 0;
            }
        }

        template<int Flags>
        Ch parse_and_append_data(xml_node<Ch> *node, Ch *&text, Ch *contents_start)
        {
            // Backup to contents start if whitespace trimming is disabled
            if (!(Flags & parse_trim_whitespace))
                text = contents_start;     
            
            // Skip until end of data
            Ch *val = text, *end;
            if (Flags & parse_normalize_whitespace)
                end = skip_and_expand_character_refs<text_pred, text_pure_with_ws_pred, Flags>(text);   
            else
                end = skip_and_expand_character_refs<text_pred, text_pure_no_ws_pred, Flags>(text);

            // Trim trailing whitespace if flag is set; leading was already trimmed by whitespace skip after >
            if (Flags & parse_trim_whitespace)
            {
                if (Flags & parse_normalize_whitespace)
                {
                    // Whitespace is already condensed to single space characters by skipping function, so just trim 1 char off the end
                    if (*(end - 1) == Ch(' '))
                        --end;
                }
                else
                {
                    // Backup until non-whitespace character is found
                    while (whitespace_pred::test(*(end - 1)))
                        --end;
                }
            }
            
            // If characters are still left between end and value (this test is only necessary if normalization is enabled)
            // Create new data node
            if (!(Flags & parse_no_data_nodes))
            {
                xml_node<Ch> *data = this->allocate_node(node_data);
                data->value(val, end - val);
                node->append_node(data);
            }

            // Add data to parent node if no data exists yet
            if (!(Flags & parse_no_element_values)) 
                if (*node->value() == Ch('\0'))
                    node->value(val, end - val);

            // Place zero terminator after value
            if (!(Flags & parse_no_string_terminators))
            {
                Ch ch = *text;
                *end = Ch('\0');
                return ch;      // Return character that ends data; this is required because zero terminator overwritten it
            }

            // Return character that ends data
            return *text;
        }

        template<int Flags>
        xml_node<Ch> *parse_cdata(Ch *&text)
        {
            // If CDATA is disabled
            if (Flags & parse_no_data_nodes)
            {
                // Skip until end of cdata
                while (text[0] != Ch(']') || text[1] != Ch(']') || text[2] != Ch('>'))
                {
                    if (!text[0])
                        BOOST_PROPERTY_TREE_RAPIDXML_PARSE_ERROR("unexpected end of data", text);
                    ++text;
                }
                text += 3;      // Skip ]]>
                return 0;       // Do not produce CDATA node
            }

            // Skip until end of cdata
            Ch *val = text;
            while (text[0] != Ch(']') || text[1] != Ch(']') || text[2] != Ch('>'))
            {
                if (!text[0])
                    BOOST_PROPERTY_TREE_RAPIDXML_PARSE_ERROR("unexpected end of data", text);
                ++text;
            }

            // Create new cdata node
            xml_node<Ch> *cdata = this->allocate_node(node_cdata);
            cdata->value(val, text - val);

            // Place zero terminator after value
            if (!(Flags & parse_no_string_terminators))
                *text = Ch('\0');

            text += 3;      // Skip ]]>
            return cdata;
        }

        template<int Flags>
        xml_node<Ch> *parse_element(Ch *&text)
        {
            // Create element node
            xml_node<Ch> *element = this->allocate_node(node_element);

            // Extract element name
            Ch *n = text;
            skip<node_name_pred, Flags>(text);
            if (text == n)
                BOOST_PROPERTY_TREE_RAPIDXML_PARSE_ERROR("expected element name", text);
            element->name(n, text - n);
            
            // Skip whitespace between element name and attributes or >
            skip<whitespace_pred, Flags>(text);

            // Parse attributes, if any
            parse_node_attributes<Flags>(text, element);

            // Determine ending type
            if (*text == Ch('>'))
            {
                ++text;
                parse_node_contents<Flags>(text, element);
            }
            else if (*text == Ch('/'))
            {
                ++text;
                if (*text != Ch('>'))
                    BOOST_PROPERTY_TREE_RAPIDXML_PARSE_ERROR("expected >", text);
                ++text;
            }
            else
                BOOST_PROPERTY_TREE_RAPIDXML_PARSE_ERROR("expected >", text);

            // Place zero terminator after name
            if (!(Flags & parse_no_string_terminators))
                element->name()[element->name_size()] = Ch('\0');

            // Return parsed element
            return element;
        }

        template<int Flags>
        xml_node<Ch> *parse_node(Ch *&text)
        {
            // Parse proper node type
            switch (text[0])
            {

            // <...
            default: 
                // Parse and append element node
                return parse_element<Flags>(text);

            // <?...
            case Ch('?'): 
                ++text;     // Skip ?
                if ((text[0] == Ch('x') || text[0] == Ch('X')) &&
                    (text[1] == Ch('m') || text[1] == Ch('M')) && 
                    (text[2] == Ch('l') || text[2] == Ch('L')) &&
                    whitespace_pred::test(text[3]))
                {
                    // '<?xml ' - xml declaration
                    text += 4;      // Skip 'xml '
                    return parse_xml_declaration<Flags>(text);
                }
                else
                {
                    // Parse PI
                    return parse_pi<Flags>(text);
                }
            
            // <!...
            case Ch('!'): 

                // Parse proper subset of <! node
                switch (text[1])    
                {
                
                // <!-
                case Ch('-'):
                    if (text[2] == Ch('-'))
                    {
                        // '<!--' - xml comment
                        text += 3;     // Skip '!--'
                        return parse_comment<Flags>(text);
                    }
                    break;

                // <![
                case Ch('['):
                    if (text[2] == Ch('C') && text[3] == Ch('D') && text[4] == Ch('A') && 
                        text[5] == Ch('T') && text[6] == Ch('A') && text[7] == Ch('['))
                    {
                        // '<![CDATA[' - cdata
                        text += 8;     // Skip '![CDATA['
                        return parse_cdata<Flags>(text);
                    }
                    break;

                // <!D
                case Ch('D'):
                    if (text[2] == Ch('O') && text[3] == Ch('C') && text[4] == Ch('T') && 
                        text[5] == Ch('Y') && text[6] == Ch('P') && text[7] == Ch('E') && 
                        whitespace_pred::test(text[8]))
                    {
                        // '<!DOCTYPE ' - doctype
                        text += 9;      // skip '!DOCTYPE '
                        return parse_doctype<Flags>(text);
                    }
                    break;

                default: break;

                }   // switch

                // Attempt to skip other, unrecognized node types starting with <!
                ++text;     // Skip !
                while (*text != Ch('>'))
                {
                    if (*text == 0)
                        BOOST_PROPERTY_TREE_RAPIDXML_PARSE_ERROR("unexpected end of data", text);
                    ++text;
                }
                ++text;     // Skip '>'
                return 0;   // No node recognized

            }
        }

        template<int Flags>
        void parse_node_contents(Ch *&text, xml_node<Ch> *node)
        {
            // For all children and text
            while (1)
            {
                // Skip whitespace between > and node contents
                Ch *contents_start = text;      // Store start of node contents before whitespace is skipped
                if (Flags & parse_trim_whitespace)
                    skip<whitespace_pred, Flags>(text);
                Ch next_char = *text;

            // After data nodes, instead of continuing the loop, control jumps here.
            // This is because zero termination inside parse_and_append_data() function
            // would wreak havoc with the above code.
            // Also, skipping whitespace after data nodes is unnecessary.
            after_data_node:    
                
                // Determine what comes next: node closing, child node, data node, or 0?
                switch (next_char)
                {
                
                // Node closing or child node
                case Ch('<'):
                    if (text[1] == Ch('/'))
                    {
                        // Node closing
                        text += 2;      // Skip '</'
                        if (Flags & parse_validate_closing_tags)
                        {
                            // Skip and validate closing tag name
                            Ch *closing_name = text;
                            skip<node_name_pred, Flags>(text);
                            if (!internal::compare(node->name(), node->name_size(), closing_name, text - closing_name, true))
                                BOOST_PROPERTY_TREE_RAPIDXML_PARSE_ERROR("invalid closing tag name", text);
                        }
                        else
                        {
                            // No validation, just skip name
                            skip<node_name_pred, Flags>(text);
                        }
                        // Skip remaining whitespace after node name
                        skip<whitespace_pred, Flags>(text);
                        if (*text != Ch('>'))
                            BOOST_PROPERTY_TREE_RAPIDXML_PARSE_ERROR("expected >", text);
                        ++text;     // Skip '>'
                        return;     // Node closed, finished parsing contents
                    }
                    else
                    {
                        // Child node
                        ++text;     // Skip '<'
                        if (xml_node<Ch> *child = parse_node<Flags>(text))
                            node->append_node(child);
                    }
                    break;

                // End of data - error
                case Ch('\0'):
                    BOOST_PROPERTY_TREE_RAPIDXML_PARSE_ERROR("unexpected end of data", text);

                // Data node
                default:
                    next_char = parse_and_append_data<Flags>(node, text, contents_start);
                    goto after_data_node;   // Bypass regular processing after data nodes

                }
            }
        }

        template<int Flags>
        void parse_node_attributes(Ch *&text, xml_node<Ch> *node)
        {
            // For all attributes 
            while (attribute_name_pred::test(*text))
            {
                // Extract attribute name
                Ch *n = text;
                ++text;     // Skip first character of attribute name
                skip<attribute_name_pred, Flags>(text);
                if (text == n)
                    BOOST_PROPERTY_TREE_RAPIDXML_PARSE_ERROR("expected attribute name", n);

                // Create new attribute
                xml_attribute<Ch> *attribute = this->allocate_attribute();
                attribute->name(n, text - n);
                node->append_attribute(attribute);

                // Skip whitespace after attribute name
                skip<whitespace_pred, Flags>(text);

                // Skip =
                if (*text != Ch('='))
                    BOOST_PROPERTY_TREE_RAPIDXML_PARSE_ERROR("expected =", text);
                ++text;

                // Add terminating zero after name
                if (!(Flags & parse_no_string_terminators))
                    attribute->name()[attribute->name_size()] = 0;

                // Skip whitespace after =
                skip<whitespace_pred, Flags>(text);

                // Skip quote and remember if it was ' or "
                Ch quote = *text;
                if (quote != Ch('\'') && quote != Ch('"'))
                    BOOST_PROPERTY_TREE_RAPIDXML_PARSE_ERROR("expected ' or \"", text);
                ++text;

                // Extract attribute value and expand char refs in it
                Ch *val = text, *end;
                const int AttFlags = Flags & ~parse_normalize_whitespace;   // No whitespace normalization in attributes
                if (quote == Ch('\''))
                    end = skip_and_expand_character_refs<attribute_value_pred<Ch('\'')>, attribute_value_pure_pred<Ch('\'')>, AttFlags>(text);
                else
                    end = skip_and_expand_character_refs<attribute_value_pred<Ch('"')>, attribute_value_pure_pred<Ch('"')>, AttFlags>(text);
                
                // Set attribute value
                attribute->value(val, end - val);
                
                // Make sure that end quote is present
                if (*text != quote)
                    BOOST_PROPERTY_TREE_RAPIDXML_PARSE_ERROR("expected ' or \"", text);
                ++text;     // Skip quote

                // Add terminating zero after value
                if (!(Flags & parse_no_string_terminators))
                    attribute->value()[attribute->value_size()] = 0;

                // Skip whitespace after attribute value
                skip<whitespace_pred, Flags>(text);
            }
        }

        inline bool operator()(Ch c1, Ch c2) const
        {
            return std::toupper(c1, m_locale) < std::toupper(c2, m_locale);
        }

        inline bool operator()(const T &t1, const T &t2) const
        {
            return std::lexicographical_compare(t1.begin(), t1.end(),
                                                t2.begin(), t2.end(), *this);
        }

        json_parser_error(const std::string &message, 
                          const std::string &filename, 
                          unsigned long line): 
            file_parser_error(message, filename, line)
        { 
        }

        info_parser_error(const std::string &message,
                          const std::string &filename,
                          unsigned long line) :
            file_parser_error(message, filename, line)
        {
        }

        template<class P> inline
        std::string prepare_bad_path_what(const std::string &what,
                                          const P &path)
        {
            return what + " (" + path.dump() + ")";
        }

        info_writer_settings(Ch indent_char = Ch(' '), unsigned indent_count = 4):
            indent_char(indent_char),
            indent_count(indent_count)
        {
        }


    template <class Ch>
    info_writer_settings<Ch> info_writer_make_settings(Ch indent_char = Ch(' '), unsigned indent_count = 4)
    {
        return info_writer_settings<Ch>(indent_char, indent_count);
    }


    inline bool validate_flags(int flags)
    {
        return (flags & ~(no_concat_text | no_comments | trim_whitespace)) == 0;
    }
