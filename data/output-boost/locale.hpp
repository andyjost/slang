
        int compare(level_type level,
                    char_type const *b1,char_type const *e1,
                    char_type const *b2,char_type const *e2) const
        {
            return do_compare(level,b1,e1,b2,e2);
        }

        string_type transform(level_type level,char_type const *b,char_type const *e) const
        {
            return do_transform(level,b,e);
        }

        long hash(level_type level,char_type const *b,char_type const *e) const
        {
            return do_hash(level,b,e);
        }

        collator(size_t refs = 0) : std::collate<CharType>(refs) 
        {
        }


        virtual ~collator()
        {
        }

        virtual int do_compare( char_type const *b1,char_type const *e1,
                                char_type const *b2,char_type const *e2) const
        {
            return do_compare(identical,b1,e1,b2,e2);
        }

        virtual string_type do_transform(char_type const *b,char_type const *e) const
        {
            return do_transform(identical,b,e);
        }

        virtual long do_hash(char_type const *b,char_type const *e) const
        {
            return do_hash(identical,b,e);
        }

        comparator(std::locale const &l=std::locale(),collator_base::level_type level=default_level) : 
            locale_(l),
            level_(level)
        {
        }

        bool operator()(std::basic_string<CharType> const &left,std::basic_string<CharType> const &right) const
        {
            return std::use_facet<collator<CharType> >(locale_).compare(level_,left,right) < 0;
        }

        hold_ptr() : ptr_(0) {}

        explicit hold_ptr(T *v) : ptr_(v) {}

        ~hold_ptr() 
        {
            delete ptr_;
        }

        T const *get() const { return ptr_; }

        T *get() { return ptr_; }

        T const &operator *() const { return *ptr_; }

        T &operator *() { return *ptr_; }

        T const *operator->() const { return ptr_; }

        T *operator->() { return ptr_; }

        T *release() { T *tmp=ptr_; ptr_=0; return tmp; }

        void reset(T *p=0)
        {
            if(ptr_) delete ptr_;
            ptr_=p;
        }

        void swap(hold_ptr &other)
        {
            T *tmp=other.ptr_;
            other.ptr_=ptr_;
            ptr_=tmp;
        }

    inline bool is_valid_codepoint(code_point v)
    {
        if(v>0x10FFFF)
            return false;
        if(0xD800 <=v && v<= 0xDFFF) // surragates
            return false;
        return true;
    }

        
        static int trail_length(char_type ci) 
        {
            unsigned char c = ci;
            if(c < 128)
                return 0;
            if(BOOST_LOCALE_UNLIKELY(c < 194))
                return -1;
            if(c < 224)
                return 1;
            if(c < 240)
                return 2;
            if(BOOST_LOCALE_LIKELY(c <=244))
                return 3;
            return -1;
        }


        static int width(code_point value)
        {
            if(value <=0x7F) {
                return 1;
            }
            else if(value <=0x7FF) {
                return 2;
            }
            else if(BOOST_LOCALE_LIKELY(value <=0xFFFF)) {
                return 3;
            }
            else {
                return 4;
            }
        }


        static bool is_trail(char_type ci)
        {
            unsigned char c=ci;
            return (c & 0xC0)==0x80;
        }


        static bool is_lead(char_type ci)
        {
            return !is_trail(ci);
        }

        
        template<typename Iterator>
        static code_point decode(Iterator &p,Iterator e)
        {
            if(BOOST_LOCALE_UNLIKELY(p==e))
                return incomplete;

            unsigned char lead = *p++;

            // First byte is fully validated here
            int trail_size = trail_length(lead);

            if(BOOST_LOCALE_UNLIKELY(trail_size < 0))
                return illegal;

            //
            // Ok as only ASCII may be of size = 0
            // also optimize for ASCII text
            //
            if(trail_size == 0)
                return lead;
            
            code_point c = lead & ((1<<(6-trail_size))-1);

            // Read the rest
            unsigned char tmp;
            switch(trail_size) {
            case 3:
                if(BOOST_LOCALE_UNLIKELY(p==e))
                    return incomplete;
                tmp = *p++;
                if (!is_trail(tmp))
                    return illegal;
                c = (c << 6) | ( tmp & 0x3F);
            case 2:
                if(BOOST_LOCALE_UNLIKELY(p==e))
                    return incomplete;
                tmp = *p++;
                if (!is_trail(tmp))
                    return illegal;
                c = (c << 6) | ( tmp & 0x3F);
            case 1:
                if(BOOST_LOCALE_UNLIKELY(p==e))
                    return incomplete;
                tmp = *p++;
                if (!is_trail(tmp))
                    return illegal;
                c = (c << 6) | ( tmp & 0x3F);
            }

            // Check code point validity: no surrogates and
            // valid range
            if(BOOST_LOCALE_UNLIKELY(!is_valid_codepoint(c)))
                return illegal;

            // make sure it is the most compact representation
            if(BOOST_LOCALE_UNLIKELY(width(c)!=trail_size + 1))
                return illegal;

            return c;

        }

        
        template<typename Iterator>
        static code_point decode_valid(Iterator &p)
        {
            unsigned char lead = *p++;
            if(lead < 192)
                return lead;

            int trail_size;

            if(lead < 224)
                trail_size = 1;
            else if(BOOST_LOCALE_LIKELY(lead < 240)) // non-BMP rare
                trail_size = 2;
            else
                trail_size = 3;
            
            code_point c = lead & ((1<<(6-trail_size))-1);

            switch(trail_size) {
            case 3:
                c = (c << 6) | ( static_cast<unsigned char>(*p++) & 0x3F);
            case 2:
                c = (c << 6) | ( static_cast<unsigned char>(*p++) & 0x3F);
            case 1:
                c = (c << 6) | ( static_cast<unsigned char>(*p++) & 0x3F);
            }

            return c;
        }




        template<typename Iterator>
        static Iterator encode(code_point value,Iterator out)
        {
            if(value <= 0x7F) {
                *out++ = static_cast<char_type>(value);
            }
            else if(value <= 0x7FF) {
                *out++ = static_cast<char_type>((value >> 6) | 0xC0);
                *out++ = static_cast<char_type>((value & 0x3F) | 0x80);
            }
            else if(BOOST_LOCALE_LIKELY(value <= 0xFFFF)) {
                *out++ = static_cast<char_type>((value >> 12) | 0xE0);
                *out++ = static_cast<char_type>(((value >> 6) & 0x3F) | 0x80);
                *out++ = static_cast<char_type>((value & 0x3F) | 0x80);
            }
            else {
                *out++ = static_cast<char_type>((value >> 18) | 0xF0);
                *out++ = static_cast<char_type>(((value >> 12) & 0x3F) | 0x80);
                *out++ = static_cast<char_type>(((value >> 6) & 0x3F) | 0x80);
                *out++ = static_cast<char_type>((value & 0x3F) | 0x80);
            }
            return out;
        }

        static bool is_first_surrogate(uint16_t x)
        {
            return 0xD800 <=x && x<= 0xDBFF;
        }

        static bool is_second_surrogate(uint16_t x)
        {
            return 0xDC00 <=x && x<= 0xDFFF;
        }

        static code_point combine_surrogate(uint16_t w1,uint16_t w2)
        {
            return ((code_point(w1 & 0x3FF) << 10) | (w2 & 0x3FF)) + 0x10000;
        }

        static int trail_length(char_type c)
        {
            if(is_first_surrogate(c))
                return 1;
            if(is_second_surrogate(c))
                return -1;
            return 0;
        }

        static bool is_trail(char_type c)
        {
            return is_second_surrogate(c);
        }

        static bool is_lead(char_type c)
        {
            return !is_second_surrogate(c);
        }


        template<typename It>
        static code_point decode(It &current,It last)
        {
            if(BOOST_LOCALE_UNLIKELY(current == last))
                return incomplete;
            uint16_t w1=*current++;
            if(BOOST_LOCALE_LIKELY(w1 < 0xD800 || 0xDFFF < w1)) {
                return w1;
            }
            if(w1 > 0xDBFF)
                return illegal;
            if(current==last)
                return incomplete;
            uint16_t w2=*current++;
            if(w2 < 0xDC00 || 0xDFFF < w2)
                return illegal;
            return combine_surrogate(w1,w2);
        }

        template<typename It>
        static code_point decode_valid(It &current)
        {
            uint16_t w1=*current++;
            if(BOOST_LOCALE_LIKELY(w1 < 0xD800 || 0xDFFF < w1)) {
                return w1;
            }
            uint16_t w2=*current++;
            return combine_surrogate(w1,w2);
        }

        static int width(code_point u)
        {
            return u>=0x10000 ? 2 : 1;
        }

        template<typename It>
        static It encode(code_point u,It out)
        {
            if(BOOST_LOCALE_LIKELY(u<=0xFFFF)) {
                *out++ = static_cast<char_type>(u);
            }
            else {
                u -= 0x10000;
                *out++ = static_cast<char_type>(0xD800 | (u>>10));
                *out++ = static_cast<char_type>(0xDC00 | (u & 0x3FF));
            }
            return out;
        }

        static int trail_length(char_type c)
        {
            if(is_valid_codepoint(c))
                return 0;
            return -1;
        }

        static bool is_trail(char_type /*c*/)
        {
            return false;
        }

        static bool is_lead(char_type /*c*/)
        {
            return true;
        }


        template<typename It>
        static code_point decode_valid(It &current)
        {
            return *current++;
        }


        template<typename It>
        static code_point decode(It &current,It last)
        {
            if(BOOST_LOCALE_UNLIKELY(current == last))
                return boost::locale::utf::incomplete;
            code_point c=*current++;
            if(BOOST_LOCALE_UNLIKELY(!is_valid_codepoint(c)))
                return boost::locale::utf::illegal;
            return c;
        }

        static int width(code_point /*u*/)
        {
            return 1;
        }

        template<typename It>
        static It encode(code_point u,It out)
        {
            *out++ = static_cast<char_type>(u);
            return out;
        }


                formattible() :
                    pointer_(0),
                    writer_(&formattible::void_write)
                {
                }

                
                formattible(formattible const &other) :
                    pointer_(other.pointer_),
                    writer_(other.writer_)
                {
                }


                formattible const &operator=(formattible const &other)
                {
                    if(this != &other) {
                        pointer_=other.pointer_;
                        writer_=other.writer_;
                    }
                    return *this;
                }

                
                template<typename Type>
                formattible(Type const &value)
                {
                    pointer_ = static_cast<void const *>(&value);
                    writer_ = &write<Type>;
                }


                template<typename Type>
                formattible const &operator=(Type const &other)
                {
                    *this = formattible(other);
                    return *this;
                }

                static void void_write(stream_type &output,void const * /*ptr*/)
                {
                    CharType empty_string[1]={0};
                    output<<empty_string;
                }


                template<typename Type>
                static void write(stream_type &output,void const *ptr)
                {
                    output << *static_cast<Type const *>(ptr);
                }

            basic_format(string_type format_string) : 
                format_(format_string),
                translate_(false),
                parameters_count_(0)
            {
            }

            template<typename Formattible>
            basic_format &operator % (Formattible const &object)
            {
                add(formattible_type(object));
                return *this;
            }

            string_type str(std::locale const &loc = std::locale()) const
            {
                std::basic_ostringstream<CharType> buffer;
                buffer.imbue(loc);
                write(buffer);
                return buffer.str();
            }

            void write(stream_type &out) const
            {
                string_type format;
                if(translate_)
                    format = message_.str(out.getloc(),ios_info::get(out).domain_id());
                else
                    format = format_;
               
                format_output(out,format);

            }

                format_guard(details::format_parser &fmt) : 
                    fmt_(&fmt),
                    restored_(false)
                {
                }

                void restore()
                {
                    if(restored_)
                        return;
                    fmt_->restore();
                    restored_ = true;
                }

                ~format_guard()
                {
                    try {
                        restore();
                    }
                    catch(...) {
                    }
                }

            
            void format_output(stream_type &out,string_type const &sformat) const
            {
                char_type obrk='{';
                char_type cbrk='}';
                char_type eq='=';
                char_type comma=',';
                char_type quote='\'';

                size_t pos = 0;
                size_t size=sformat.size();
                CharType const *format=sformat.c_str();
                while(format[pos]!=0) {
                    if(format[pos] != obrk) {
                        if(format[pos]==cbrk && format[pos+1]==cbrk) {
                            out << cbrk;
                            pos+=2;
                        }
                        else {
                            out<<format[pos];
                            pos++;
                        }
                        continue;
                    }

                    if(pos+1 < size && format[pos+1]==obrk) {
                        out << obrk;
                        pos+=2;
                        continue;
                    }
                    pos++;
                  
                    details::format_parser fmt(out,static_cast<void *>(&out),&basic_format::imbue_locale);

                    format_guard guard(fmt);

                    while(pos < size) { 
                        std::string key;
                        std::string svalue;
                        string_type value;
                        bool use_svalue = true;
                        for(;format[pos];pos++) {
                            char_type c=format[pos];
                            if(c==comma || c==eq || c==cbrk)
                                break;
                            else {
                                key+=static_cast<char>(c);
                            }
                        }

                        if(format[pos]==eq) {
                            pos++;
                            if(format[pos]==quote) {
                                pos++;
                                use_svalue = false;
                                while(format[pos]) {
                                    if(format[pos]==quote) {
                                        if(format[pos+1]==quote) {
                                            value+=quote;
                                            pos+=2;
                                        }
                                        else {
                                            pos++;
                                            break;
                                        }
                                    }
                                    else {
                                        value+=format[pos];
                                        pos++;
                                    }
                                }
                            }
                            else {
                                char_type c;
                                while((c=format[pos])!=0 && c!=comma && c!=cbrk) {
                                    svalue+=static_cast<char>(c);
                                    pos++;
                                }
                            }
                        }

                        if(use_svalue) {
                            fmt.set_one_flag(key,svalue);
                        }
                        else 
                            fmt.set_flag_with_str(key,value);
                        
                        if(format[pos]==comma) {
                            pos++;
                            continue;
                        }
                        else if(format[pos]==cbrk)  {
                            unsigned position = fmt.get_position();
                            out << get(position);
                            guard.restore();
                            pos++;
                            break;
                        }
                        else {                        
                            guard.restore();
                            break;
                        }
                    }
                }
            }


            void add(formattible_type const &param)
            {
                if(parameters_count_ >= base_params_)
                    ext_params_.push_back(param);
                else 
                    parameters_[parameters_count_] = param;
                parameters_count_++;
            }


            formattible_type get(unsigned id) const
            {
                if(id >= parameters_count_)
                    return formattible_type();
                else if(id >= base_params_)
                    return ext_params_[id - base_params_];
                else
                    return parameters_[id];
            }


            static void imbue_locale(void *ptr,std::locale const &l)
            {
                reinterpret_cast<stream_type *>(ptr)->imbue(l);
            }

            
            inline std::ios_base & posix(std::ios_base & ios)
            {
                ios_info::get(ios).display_flags(flags::posix);
                return ios;
            }

            inline std::ios_base & number(std::ios_base & ios)
            {
                ios_info::get(ios).display_flags(flags::number);
                return ios;
            }

            inline std::ios_base & currency(std::ios_base & ios)
            {
                ios_info::get(ios).display_flags(flags::currency);
                return ios;
            }

            inline std::ios_base & percent(std::ios_base & ios)
            {
                ios_info::get(ios).display_flags(flags::percent);
                return ios;
            }

            inline std::ios_base & date(std::ios_base & ios)
            {
                ios_info::get(ios).display_flags(flags::date);
                return ios;
            }

            inline std::ios_base & time(std::ios_base & ios)
            {
                ios_info::get(ios).display_flags(flags::time);
                return ios;
            }

            inline std::ios_base & datetime(std::ios_base & ios)
            {
                ios_info::get(ios).display_flags(flags::datetime);
                return ios;
            }

            inline std::ios_base & strftime(std::ios_base & ios)
            {
                ios_info::get(ios).display_flags(flags::strftime);
                return ios;
            }

            inline std::ios_base & spellout(std::ios_base & ios)
            {
                ios_info::get(ios).display_flags(flags::spellout);
                return ios;
            }

            inline std::ios_base & ordinal(std::ios_base & ios)
            {
                ios_info::get(ios).display_flags(flags::ordinal);
                return ios;
            }

            inline std::ios_base & currency_default(std::ios_base & ios)
            {
                ios_info::get(ios).currency_flags(flags::currency_default);
                return ios;
            }

            inline std::ios_base & currency_iso(std::ios_base & ios)
            {
                ios_info::get(ios).currency_flags(flags::currency_iso);
                return ios;
            }

            inline std::ios_base & currency_national(std::ios_base & ios)
            {
                ios_info::get(ios).currency_flags(flags::currency_national);
                return ios;
            }

            inline std::ios_base & time_default(std::ios_base & ios)
            {
                ios_info::get(ios).time_flags(flags::time_default);
                return ios;
            }

            inline std::ios_base & time_short(std::ios_base & ios)
            {
                ios_info::get(ios).time_flags(flags::time_short);
                return ios;
            }

            inline std::ios_base & time_medium(std::ios_base & ios)
            {
                ios_info::get(ios).time_flags(flags::time_medium);
                return ios;
            }

            inline std::ios_base & time_long(std::ios_base & ios)
            {
                ios_info::get(ios).time_flags(flags::time_long);
                return ios;
            }

            inline std::ios_base & time_full(std::ios_base & ios)
            {
                ios_info::get(ios).time_flags(flags::time_full);
                return ios;
            }

            inline std::ios_base & date_default(std::ios_base & ios)
            {
                ios_info::get(ios).date_flags(flags::date_default);
                return ios;
            }

            inline std::ios_base & date_short(std::ios_base & ios)
            {
                ios_info::get(ios).date_flags(flags::date_short);
                return ios;
            }

            inline std::ios_base & date_medium(std::ios_base & ios)
            {
                ios_info::get(ios).date_flags(flags::date_medium);
                return ios;
            }

            inline std::ios_base & date_long(std::ios_base & ios)
            {
                ios_info::get(ios).date_flags(flags::date_long);
                return ios;
            }

            inline std::ios_base & date_full(std::ios_base & ios)
            {
                ios_info::get(ios).date_flags(flags::date_full);
                return ios;
            }


                    void apply(std::basic_ios<CharType> &ios) const
                    {
                        ios_info::get(ios).date_time_pattern(ftime);
                        as::strftime(ios);
                    }

            inline std::ios_base &gmt(std::ios_base &ios)
            {
                ios_info::get(ios).time_zone("GMT");
                return ios;
            }

            inline std::ios_base &local_time(std::ios_base &ios)
            {
                ios_info::get(ios).time_zone(time_zone::global());
                return ios;
            }

            inline 
            #ifdef BOOST_LOCALE_DOXYGEN
            unspecified_type
            #else
            details::set_timezone 
            #endif
            time_zone(char const *id) 
            {
                details::set_timezone tz;
                tz.id=id;
                return tz;
            }

            
            inline
            std::string between(char const *text,
                                std::string const &to_encoding,
                                std::string const &from_encoding,
                                method_type how=default_method)
            {
                char const *end=text;
                while(*end)
                    end++;
                return boost::locale::conv::between(text,end,to_encoding,from_encoding,how);
            }

                period_type(marks::period_mark m = marks::invalid) : mark_(m) 
                {
                }

                marks::period_mark mark() const
                {
                    return mark_;
                }

                bool operator==(period_type const &other) const
                {
                    return mark()==other.mark();
                }

                bool operator!=(period_type const &other) const
                {
                    return mark()!=other.mark();
                }


            virtual ~abstract_calendar()
            {
            }


            localization_backend()
            {
            }

            
            virtual ~localization_backend()
            {
            }

            message_format(size_t refs = 0) : 
                base_message_format<CharType>(refs)
            {
            }

            virtual ~message_format()
            {
            }

            inline bool is_us_ascii_char(char c)
            {
                // works for null terminated strings regardless char "signness"
                return 0<c && c<0x7F; 
            }

            inline bool is_us_ascii_string(char const *msg)
            {
                while(*msg) {
                    if(!is_us_ascii_char(*msg++))
                        return false;
                }
                return true;
            }

                static CharType const *cast(CharType const *msg,std::basic_string<CharType> &/*unused*/)
                {
                    return msg;
                }

                static char const *cast(char const *msg,std::string &buffer)
                {
                    if(is_us_ascii_string(msg))
                        return msg;
                    buffer.reserve(strlen(msg));
                    char c;
                    while((c=*msg++)!=0) {
                        if(is_us_ascii_char(c))
                            buffer+=c;
                    }
                    return buffer.c_str();
                }

            basic_message() :
                n_(0),
                c_id_(0),
                c_context_(0),
                c_plural_(0)
            {
            }

            explicit basic_message(char_type const *id) :
                n_(0),
                c_id_(id),
                c_context_(0),
                c_plural_(0)
            {
            }

            explicit basic_message(char_type const *single,char_type const *plural,int n) :
                n_(n),
                c_id_(single),
                c_context_(0),
                c_plural_(plural)
            {
            }

            explicit basic_message(char_type const *context,char_type const *id) :
                n_(0),
                c_id_(id),
                c_context_(context),
                c_plural_(0)
            {
            }

            explicit basic_message(char_type const *context,char_type const *single,char_type const *plural,int n) :
                n_(n),
                c_id_(single),
                c_context_(context),
                c_plural_(plural)
            {
            }

            basic_message(basic_message const &other) :
                n_(other.n_),
                c_id_(other.c_id_),
                c_context_(other.c_context_),
                c_plural_(other.c_plural_),
                id_(other.id_),
                context_(other.context_),
                plural_(other.plural_)
            {
            }

            basic_message const &operator=(basic_message const &other)
            {
                if(this==&other) {
                    return *this;
                }
                basic_message tmp(other);
                swap(tmp);
                return *this;
            }

            void swap(basic_message &other)
            {
                std::swap(n_,other.n_);
                std::swap(c_id_,other.c_id_);
                std::swap(c_context_,other.c_context_);
                std::swap(c_plural_,other.c_plural_);

                id_.swap(other.id_);
                context_.swap(other.context_);
                plural_.swap(other.plural_);
            }

            date_time_period operator+() const { return *this; }

            date_time_period operator-() const { return date_time_period(type,-value); }

            date_time_period(period::period_type f=period::period_type(),int v=1) : type(f), value(v) {}

            inline period_type invalid(){ return period_type(marks::invalid); }

            inline period_type era(){ return period_type(marks::era); }

            inline period_type year(){ return period_type(marks::year); }

            inline period_type extended_year(){ return period_type(marks::extended_year); }

            inline period_type month(){ return period_type(marks::month); }

            inline period_type day(){ return period_type(marks::day); }

            inline period_type day_of_year(){ return period_type(marks::day_of_year); }

            inline period_type day_of_week(){ return period_type(marks::day_of_week); }

            inline period_type day_of_week_in_month(){ return period_type(marks::day_of_week_in_month); }

            inline period_type day_of_week_local(){ return period_type(marks::day_of_week_local); }

            inline period_type hour(){ return period_type(marks::hour); }

            inline period_type hour_12(){ return period_type(marks::hour_12); }

            inline period_type am_pm(){ return period_type(marks::am_pm); }

            inline period_type minute(){ return period_type(marks::minute); }

            inline period_type second(){ return period_type(marks::second); }

            inline period_type week_of_year(){ return period_type(marks::week_of_year); }

            inline period_type week_of_month(){ return period_type(marks::week_of_month); }

            inline period_type first_day_of_week(){ return period_type(marks::first_day_of_week); }

            inline date_time_period era(int v) { return date_time_period(era(),v); }

            inline date_time_period year(int v) { return date_time_period(year(),v); }

            inline date_time_period extended_year(int v) { return date_time_period(extended_year(),v); }

            inline date_time_period month(int v) { return date_time_period(month(),v); }

            inline date_time_period day(int v) { return date_time_period(day(),v); }

            inline date_time_period day_of_year(int v) { return date_time_period(day_of_year(),v); }

            inline date_time_period day_of_week(int v) { return date_time_period(day_of_week(),v); }

            inline date_time_period day_of_week_in_month(int v) { return date_time_period(day_of_week_in_month(),v); }

            inline date_time_period day_of_week_local(int v) { return date_time_period(day_of_week_local(),v); }

            inline date_time_period hour(int v) { return date_time_period(hour(),v); }

            inline date_time_period hour_12(int v) { return date_time_period(hour_12(),v); }

            inline date_time_period am_pm(int v) { return date_time_period(am_pm(),v); }

            inline date_time_period minute(int v) { return date_time_period(minute(),v); }

            inline date_time_period second(int v) { return date_time_period(second(),v); }

            inline date_time_period week_of_year(int v) { return date_time_period(week_of_year(),v); }

            inline date_time_period week_of_month(int v) { return date_time_period(week_of_month(),v); }

            inline date_time_period first_day_of_week(int v) { return date_time_period(first_day_of_week(),v); }

            inline date_time_period january() { return date_time_period(month(),0); }

            inline date_time_period february() { return date_time_period(month(),1); }

            inline date_time_period march() { return date_time_period(month(),2); }

            inline date_time_period april() { return date_time_period(month(),3); }

            inline date_time_period may() { return date_time_period(month(),4); }

            inline date_time_period june() { return date_time_period(month(),5); }

            inline date_time_period july() { return date_time_period(month(),6); }

            inline date_time_period august() { return date_time_period(month(),7); }

            inline date_time_period september() { return date_time_period(month(),8); }

            inline date_time_period october() { return date_time_period(month(),9); }

            inline date_time_period november() { return date_time_period(month(),10); }

            inline date_time_period december() { return date_time_period(month(),11); }

            inline date_time_period sunday() { return date_time_period(day_of_week(),1); }

            inline date_time_period monday() { return date_time_period(day_of_week(),2); }

            inline date_time_period tuesday() { return date_time_period(day_of_week(),3); }

            inline date_time_period wednesday() { return date_time_period(day_of_week(),4); }

            inline date_time_period thursday() { return date_time_period(day_of_week(),5); }

            inline date_time_period friday() { return date_time_period(day_of_week(),6); }

            inline date_time_period saturday() { return date_time_period(day_of_week(),7); }

            inline date_time_period am() { return date_time_period(am_pm(),0); }

            inline date_time_period pm() { return date_time_period(am_pm(),1); }

            inline date_time_period operator+(period::period_type f) 
            {
                return date_time_period(f);
            }

            inline date_time_period operator-(period::period_type f)
            {
                return date_time_period(f,-1);
            }

            template<typename T>
            date_time_period operator*(period::period_type f,T v)
            {
                return date_time_period(f,v);
            }

            template<typename T>
            date_time_period operator*(T v,date_time_period f)
            {
                return date_time_period(f.type,f.value*v);
            }

            template<typename T>
            date_time_period operator*(date_time_period f,T v)
            {
                return date_time_period(f.type,f.value*v);
            }

            date_time_period_set()
            {
            }

            date_time_period_set(date_time_period const &fl)
            {
                basic_[0]=fl;
            }

            void add(date_time_period f)
            {
                size_t n=size();
                if(n < 4)
                    basic_[n]=f;
                else
                    periods_.push_back(f);
            }

            size_t size() const
            {
                if(basic_[0].type == period::period_type())
                    return 0;
                if(basic_[1].type == period::period_type())
                    return 1;
                if(basic_[2].type == period::period_type())
                    return 2;
                if(basic_[3].type == period::period_type())
                    return 3;
                return 4+periods_.size();
            }

            date_time_period const &operator[](size_t n) const 
            {
                if(n >= size())
                    throw std::out_of_range("Invalid index to date_time_period");
                if(n < 4)
                    return basic_[n];
                else
                    return periods_[n-4];
            }

        inline date_time_period_set operator+(date_time_period_set const &a,date_time_period_set const &b)
        {
            date_time_period_set s(a);
            for(unsigned i=0;i<b.size();i++)
                s.add(b[i]);
            return s;
        }

        inline date_time_period_set operator-(date_time_period_set const &a,date_time_period_set const &b)
        {
            date_time_period_set s(a);
            for(unsigned i=0;i<b.size();i++)
                s.add(-b[i]);
            return s;
        }

        
        virtual ~base_converter() 
        {
        }

        virtual int max_len() const 
        {
            return 1;
        }

        virtual bool is_thread_safe() const 
        {
            return false;
        }

        virtual base_converter *clone() const 
        {
            BOOST_ASSERT(typeid(*this)==typeid(base_converter));
            return new base_converter();
        }

        virtual uint32_t to_unicode(char const *&begin,char const *end) 
        {
            if(begin == end)
                return incomplete;
            unsigned char cp = *begin;
            if(cp <= 0x7F) {
                begin++;
                return cp;
            }
            return illegal;
        }


        virtual uint32_t from_unicode(uint32_t u,char *begin,char const *end) 
        {
            if(begin==end)
                return incomplete;
            if(u >= 0x80)
                return illegal;
            *begin = static_cast<char>(u);
            return 1;
        }

        messages_info() :
            language("C"),
            locale_category("LC_MESSAGES")
        {
        }

            domain() {}

            bool operator==(domain const &other) const
            {
                return name==other.name;
            }

            bool operator!=(domain const &other) const
            {
                return !(*this==other);
            }




                    static index_type map(boundary_type t,IteratorType b,IteratorType e,std::locale const &l)
                    {
                        index_type result;

                        //
                        // Optimize for most common cases
                        //
                        // C++0x requires that string is continious in memory and all known
                        // string implementations
                        // do this because of c_str() support. 
                        //

                        if(linear_iterator_traits<char_type,IteratorType>::is_linear && b!=e)
                        {
                            char_type const *begin = &*b;
                            char_type const *end = begin + (e-b);
                            index_type tmp=std::use_facet<boundary_indexing<char_type> >(l).map(t,begin,end);
                            result.swap(tmp);
                        }
                        else {
                            std::basic_string<char_type> str(b,e);
                            index_type tmp = std::use_facet<boundary_indexing<char_type> >(l).map(t,str.c_str(),str.c_str()+str.size());
                            result.swap(tmp);
                        }
                        return result;
                    }



                    mapping(boundary_type type,
                            base_iterator begin,
                            base_iterator end,
                            std::locale const &loc) 
                        :   
                            index_(new index_type()),
                            begin_(begin),
                            end_(end)
                    {
                        index_type idx=details::mapping_traits<base_iterator>::map(type,begin,end,loc);
                        index_->swap(idx);
                    }


                    mapping()
                    {
                    }

                    
                    segment_index_iterator() : current_(0,0),map_(0)
                    {
                    }

                    
                    boundary_point_index_iterator() : current_(0),map_(0)
                    {
                    }

                segment_index() : mask_(0xFFFFFFFFu),full_select_(false)
                {
                }

                void map(boundary_type type,base_iterator begin,base_iterator end,std::locale const &loc=std::locale())
                {
                    map_ = mapping_type(type,begin,end,loc);
                }

                iterator begin() const
                {
                    return iterator(true,&map_,mask_,full_select_);
                }

                iterator end() const
                {
                    return iterator(false,&map_,mask_,full_select_);
                }

                iterator find(base_iterator p) const
                {
                    return iterator(p,&map_,mask_,full_select_);
                }

                rule_type rule() const
                {
                    return mask_;
                }


                bool full_select()  const 
                {
                    return full_select_;
                }


                void full_select(bool v) 
                {
                    full_select_ = v;
                }

                boundary_point_index() : mask_(0xFFFFFFFFu)
                {
                }

                void map(boundary_type type,base_iterator begin,base_iterator end,std::locale const &loc=std::locale())
                {
                    map_ = mapping_type(type,begin,end,loc);
                }

                iterator begin() const
                {
                    return iterator(true,&map_,mask_);
                }

                iterator end() const
                {
                    return iterator(false,&map_,mask_);
                }

                iterator find(base_iterator p) const
                {
                    return iterator(p,&map_,mask_);
                }

                rule_type rule() const
                {
                    return mask_;
                }

            template<typename BaseIterator>
            segment_index<BaseIterator>::segment_index(boundary_point_index<BaseIterator> const &other) :
                map_(other.map_),
                mask_(0xFFFFFFFFu),
                full_select_(false)
            {
            }

            
            template<typename BaseIterator>
            boundary_point_index<BaseIterator>::boundary_point_index(segment_index<BaseIterator> const &other) :
                map_(other.map_),
                mask_(0xFFFFFFFFu)
            {
            }


            template<typename BaseIterator>
            segment_index<BaseIterator> const &segment_index<BaseIterator>::operator=(boundary_point_index<BaseIterator> const &other)
            {
                map_ = other.map_;
                return *this;
            }

            
            template<typename BaseIterator>
            boundary_point_index<BaseIterator> const &boundary_point_index<BaseIterator>::operator=(segment_index<BaseIterator> const &other)
            {
                map_ = other.map_;
                return *this;
            }

        boundary_point() : rule_(0) {}

        void iterator(iterator_type i)
        {
            iterator_ = i;
        }

        void rule(rule_type r)
        {
            rule_ = r;
        }

        iterator_type iterator() const 
        {
            return iterator_;
        }

        bool operator==(boundary_point const &other) const
        {
            return iterator_ == other.iterator_ && rule_ = other.rule_;
        }

        bool operator!=(boundary_point const &other) const
        {
            return !(*this==other);
        }

        bool operator==(iterator_type const &other) const
        {
            return iterator_ == other;
        }

        bool operator!=(iterator_type const &other) const
        {
            return iterator_ != other;
        }

        operator iterator_type ()const
        {
            return iterator_;
        }

    template<typename BaseIterator>
    bool operator==(BaseIterator const &l,boundary_point<BaseIterator> const &r)
    {
        return r==l;
    }

    template<typename BaseIterator>
    bool operator!=(BaseIterator const &l,boundary_point<BaseIterator> const &r)
    {
        return r!=l;
    }

        template<typename LeftIterator,typename RightIterator>
        int compare_text(LeftIterator l_begin,LeftIterator l_end,RightIterator r_begin,RightIterator r_end)
        {
            typedef LeftIterator left_iterator;
            typedef RightIterator right_iterator;
            typedef typename std::iterator_traits<left_iterator>::value_type char_type;
            typedef std::char_traits<char_type> traits;
            while(l_begin!=l_end && r_begin!=r_end) {
                char_type lchar = *l_begin++;
                char_type rchar = *r_begin++;
                if(traits::eq(lchar,rchar))
                    continue;
                if(traits::lt(lchar,rchar))
                    return -1;
                else
                    return 1;
            }
            if(l_begin==l_end && r_begin==r_end)
                return 0;
            if(l_begin==l_end)
                return -1;
            else
                return 1;
        }



        template<typename Left,typename Right>
        int compare_text(Left const &l,Right const &r)
        {
            return compare_text(l.begin(),l.end(),r.begin(),r.end());
        }

        
        template<typename Left,typename Char>
        int compare_string(Left const &l,Char const *begin)
        {
            Char const *end = begin;
            while(*end!=0)
                end++;
            return compare_text(l.begin(),l.end(),begin,end);
        }


        template<typename Right,typename Char>
        int compare_string(Char const *begin,Right const &r)
        {
            Char const *end = begin;
            while(*end!=0)
                end++;
            return compare_text(begin,end,r.begin(),r.end());
        }

        segment() {}

        void begin(iterator const &v)
        {
            this->first = v;
        }

         void end(iterator const &v)
        {
            this->second = v;
        }

        IteratorType begin() const 
        {
            return this->first;
        }

        IteratorType end() const
        {
            return this->second;
        }

    template<typename IteratorL,typename IteratorR>
    bool operator==(segment<IteratorL> const &l,segment<IteratorR> const &r)
    {
        return details::compare_text(l,r) == 0; 
    }

    template<typename IteratorL,typename IteratorR>
    bool operator!=(segment<IteratorL> const &l,segment<IteratorR> const &r)
    {
        return details::compare_text(l,r) != 0; 
    }

    template<typename IteratorL,typename IteratorR>
    bool operator<(segment<IteratorL> const &l,segment<IteratorR> const &r)
    {
        return details::compare_text(l,r) < 0; 
    }

    template<typename IteratorL,typename IteratorR>
    bool operator<=(segment<IteratorL> const &l,segment<IteratorR> const &r)
    {
        return details::compare_text(l,r) <= 0; 
    }

    template<typename IteratorL,typename IteratorR>
    bool operator>(segment<IteratorL> const &l,segment<IteratorR> const &r)
    {
        return details::compare_text(l,r) > 0; 
    }

    template<typename IteratorL,typename IteratorR>
    bool operator>=(segment<IteratorL> const &l,segment<IteratorR> const &r)
    {
        return details::compare_text(l,r) >= 0; 
    }

    template<typename CharType,typename IteratorR>
    bool operator==(CharType const *l,segment<IteratorR> const &r)
    {
        return details::compare_string(l,r) == 0; 
    }

    template<typename CharType,typename IteratorR>
    bool operator!=(CharType const *l,segment<IteratorR> const &r)
    {
        return details::compare_string(l,r) != 0; 
    }

    template<typename CharType,typename IteratorR>
    bool operator<(CharType const *l,segment<IteratorR> const &r)
    {
        return details::compare_string(l,r) < 0; 
    }

    template<typename CharType,typename IteratorR>
    bool operator<=(CharType const *l,segment<IteratorR> const &r)
    {
        return details::compare_string(l,r) <= 0; 
    }

    template<typename CharType,typename IteratorR>
    bool operator>(CharType const *l,segment<IteratorR> const &r)
    {
        return details::compare_string(l,r) > 0; 
    }

    template<typename CharType,typename IteratorR>
    bool operator>=(CharType const *l,segment<IteratorR> const &r)
    {
        return details::compare_string(l,r) >= 0; 
    }

    template<typename Iterator,typename CharType>
    bool operator==(segment<Iterator> const &l,CharType const *r)
    {
        return details::compare_string(l,r) == 0; 
    }

    template<typename Iterator,typename CharType>
    bool operator!=(segment<Iterator> const &l,CharType const *r)
    {
        return details::compare_string(l,r) != 0; 
    }

    template<typename Iterator,typename CharType>
    bool operator<(segment<Iterator> const &l,CharType const *r)
    {
        return details::compare_string(l,r) < 0; 
    }

    template<typename Iterator,typename CharType>
    bool operator<=(segment<Iterator> const &l,CharType const *r)
    {
        return details::compare_string(l,r) <= 0; 
    }

    template<typename Iterator,typename CharType>
    bool operator>(segment<Iterator> const &l,CharType const *r)
    {
        return details::compare_string(l,r) > 0; 
    }

    template<typename Iterator,typename CharType>
    bool operator>=(segment<Iterator> const &l,CharType const *r)
    {
        return details::compare_string(l,r) >= 0; 
    }

                break_info() : 
                    offset(0),
                    rule(0)
                {
                }

                bool operator<(break_info const &other) const
                {
                    return offset < other.offset;
                }

            inline rule_type boundary_rule(boundary_type t)
            {
                switch(t) {
                case character: return character_mask;
                case word:      return word_mask;
                case sentence:  return sentence_mask;
                case line:      return line_mask;
                default:        return 0;
                }
            }
