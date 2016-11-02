
        basic_option() 
        : position_key(-1)
        , unregistered(false) 
        , case_insensitive(false)
        {}

        eof_iterator()
        : m_at_eof(false)
        {}

        ValueType& value()
        {
            return m_value;
        }

        void found_eof()
        {
            m_at_eof = true;
        }

    
        void increment() 
        {
            static_cast<Derived&>(*this).get();
        }

    
        bool equal(const eof_iterator& other) const
        {
            if (m_at_eof && other.m_at_eof)
                return true;
            else
                return false;
        }

        
        const ValueType& dereference() const
        {
            return m_value;
        }

        explicit basic_parsed_options(const options_description* xdescription, int options_prefix = 0) 
        : description(xdescription), m_options_prefix(options_prefix) {}
eof_iterator():m_at_eof(false){}
ValueType&value(){returnm_value;}
voidfound_eof(){m_at_eof=true;}
voidincrement(){static_cast<Derived&>(*this).get();}
boolequal(consteof_iterator&other)const{if(m_at_eof&&other.m_at_eof)returntrue;elsereturnfalse;}
constValueType&dereference()const{returnm_value;}

        environment_iterator(char** environment)
        : m_environment(environment)
        {
            get();
        }

        
        environment_iterator()
        {
            found_eof();
        }

        
        void get()
        {
            if (*m_environment == 0)
                found_eof();
            else {
                std::string s(*m_environment);
                std::string::size_type n = s.find('=');
                assert(n != s.npos);
                value().first = s.substr(0, n);
                value().second = s.substr(n+1);
            }            
            ++m_environment;
        }


    inline std::string strip_prefixes(const std::string& text)
    {
        return text.substr(text.find_last_of("-/") + 1);
    }

        virtual ~typed_value_base() {}

        typed_value(T* store_to) 
        : m_store_to(store_to), m_composing(false),
          m_multitoken(false), m_zero_tokens(false),
          m_required(false)
        {}

        typed_value* default_value(const T& v)
        {
            m_default_value = boost::any(v);
            m_default_value_as_text = boost::lexical_cast<std::string>(v);
            return this;
        }

        typed_value* implicit_value(const T &v)
        {
            m_implicit_value = boost::any(v);
            m_implicit_value_as_text =
                boost::lexical_cast<std::string>(v);
            return this;
        }

        typed_value* value_name(const std::string& name)
        {
            m_value_name = name;
            return this;
        }

        typed_value* notifier(function1<void, const T&> f)
        {
            m_notifier = f;
            return this;
        }

        typed_value* composing()
        {
            m_composing = true;
            return this;
        }

        typed_value* multitoken()
        {
            m_multitoken = true;
            return this;
        }

        typed_value* zero_tokens() 
        {
            m_zero_tokens = true;
            return this;
        }

        typed_value* required()
        {
            m_required = true;
            return this;
        }


        bool is_composing() const { return m_composing; }


        unsigned min_tokens() const
        {
            if (m_zero_tokens || !m_implicit_value.empty()) {
                return 0;
            } else {
                return 1;
            }
        }


        unsigned max_tokens() const {
            if (m_multitoken) {
                return 32000;
            } else if (m_zero_tokens) {
                return 0;
            } else {
                return 1;
            }
        }


        bool is_required() const { return m_required; }

        virtual bool apply_default(boost::any& value_store) const
        {
            if (m_default_value.empty()) {
                return false;
            } else {
                value_store = m_default_value;
                return true;
            }
        }

        
        const std::type_info& value_type() const
        {
            return typeid(T);
        }

        common_config_file_iterator() { found_eof(); }


        virtual ~common_config_file_iterator() {}

        virtual bool getline(std::string&) { return false; }

        basic_config_file_iterator()
        {
            found_eof();
        }

        void operator()(void const *) const {}

    template<class T, class charT>
    void validate(boost::any& v, 
                  const std::vector< std::basic_string<charT> >& xs, 
                  T*, long)
    {
        validators::check_first_occurrence(v);
        std::basic_string<charT> s(validators::get_single_string(xs));
        try {
            v = any(lexical_cast<T>(s));
        }
        catch(const bad_lexical_cast&) {
            boost::throw_exception(invalid_option_value(s));
        }
    }
