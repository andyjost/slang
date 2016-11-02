

        explicit factory(allocator_type const & a = allocator_type())
          : allocator_type(a)
        { }

            inline deleter(allocator_type const& that) 
              : allocator_type(that)
            { }


            allocator_type& get_allocator() const
            {
                return *const_cast<allocator_type*>(
                    static_cast<allocator_type const*>(this));
            }


            void operator()(value_type* ptr) const
            {
                if (!! ptr) ptr->~value_type();
                const_cast<allocator_type*>(static_cast<allocator_type const*>(
                    this))->deallocate(ptr,1);
            }


        inline allocator_type& get_allocator() const
        {
            return *const_cast<allocator_type*>(
                static_cast<allocator_type const*>(this));
        }


        inline result_type make_pointer(value_type* ptr, boost::non_type<
            factory_alloc_propagation,factory_passes_alloc_to_smart_pointer>)
        const
        {
            return result_type(ptr,deleter(this->get_allocator()));
        }


        value_factory()
        { }

        forward_adapter(Function const& f = Function()) 
          : Function(f) 
        { }


        Function       & target_function()       { return *this; }

        Function const & target_function() const { return *this; }

        forward_adapter(Function const& f = Function())
          : Function(f) 
        { }


        Function const & target_function() const { return *this; }

        forward_adapter(Function& f)
          : ref_function(f) 
        { }


        Function & target_function() const { return this->ref_function; }

        lightweight_forward_adapter(Function const& f = Function()) 
          : Function(f) 
        { }


        Function       & target_function()       { return *this; }

        Function const & target_function() const { return *this; }

        lightweight_forward_adapter(Function const& f = Function())
          : Function(f) 
        { }


        Function const & target_function() const { return *this; }

        lightweight_forward_adapter(Function& f)
          : ref_function(f) 
        { }


        Function & target_function() const { return this->ref_function; }

        std::size_t operator()(T const& val) const
        {
            return hash_value(val);
        }

        template <class T>
        inline std::size_t hash_value_signed(T val)
        {
             const int size_t_bits = std::numeric_limits<std::size_t>::digits;
             // ceiling(std::numeric_limits<T>::digits / size_t_bits) - 1
             const int length = (std::numeric_limits<T>::digits - 1)
                 / size_t_bits;

             std::size_t seed = 0;
             T positive = val < 0 ? -1 - val : val;

             // Hopefully, this loop can be unrolled.
             for(unsigned int i = length * size_t_bits; i > 0; i -= size_t_bits)
             {
                 seed ^= (std::size_t) (positive >> i) + (seed<<6) + (seed>>2);
             }
             seed ^= (std::size_t) val + (seed<<6) + (seed>>2);

             return seed;
        }


        template <class T>
        inline std::size_t hash_value_unsigned(T val)
        {
             const int size_t_bits = std::numeric_limits<std::size_t>::digits;
             // ceiling(std::numeric_limits<T>::digits / size_t_bits) - 1
             const int length = (std::numeric_limits<T>::digits - 1)
                 / size_t_bits;

             std::size_t seed = 0;

             // Hopefully, this loop can be unrolled.
             for(unsigned int i = length * size_t_bits; i > 0; i -= size_t_bits)
             {
                 seed ^= (std::size_t) (val >> i) + (seed<<6) + (seed>>2);
             }
             seed ^= (std::size_t) val + (seed<<6) + (seed>>2);

             return seed;
        }


    template <typename T>
    typename boost::hash_detail::basic_numbers<T>::type hash_value(T v)
    {
        return static_cast<std::size_t>(v);
    }


    template <typename T>
    typename boost::hash_detail::long_numbers<T>::type hash_value(T v)
    {
        return hash_detail::hash_value_signed(v);
    }


    template <typename T>
    typename boost::hash_detail::ulong_numbers<T>::type hash_value(T v)
    {
        return hash_detail::hash_value_unsigned(v);
    }
 \
        std::size_t operator()(const type v) const \
        { \
            return boost::hash_value(v); \
        } \
    };

#define BOOST_HASH_SPECIALIZE_REF(type) \
    template <> struct hash<type> \
         : public std::unary_function<type, std::size_t> \
    { \
        std::size_t operator()(type const& v) const \
        { \
            return boost::hash_value(v); \
        } \
    }; \
    \
    template <> struct hash<const type> \
         : public std::unary_function<const type, std::size_t> \
    { \
        std::size_t operator()(type const& v) const \
        { \
            return boost::hash_value(v); \
        } \
    };
#endif

    BOOST_HASH_SPECIALIZE(bool)

        inline void hash_float_combine(std::size_t& seed, std::size_t value)
        {
            seed ^= value + (seed<<6) + (seed>>2);
        }


        inline std::size_t hash_binary(char* ptr, std::size_t length)
        {
            std::size_t seed = 0;

            if (length >= sizeof(std::size_t)) {
                seed = *(std::size_t*) ptr;
                length -= sizeof(std::size_t);
                ptr += sizeof(std::size_t);

                while(length >= sizeof(std::size_t)) {
                    std::size_t buffer = 0;
                    std::memcpy(&buffer, ptr, sizeof(std::size_t));
                    hash_float_combine(seed, buffer);
                    length -= sizeof(std::size_t);
                    ptr += sizeof(std::size_t);
                }
            }

            if (length > 0) {
                std::size_t buffer = 0;
                std::memcpy(&buffer, ptr, length);
                hash_float_combine(seed, buffer);
            }

            return seed;
        }


        template <typename Float>
        inline std::size_t float_hash_impl(Float v,
            BOOST_DEDUCED_TYPENAME boost::enable_if_c<
                std::numeric_limits<Float>::is_iec559 &&
                std::numeric_limits<Float>::digits == 24 &&
                std::numeric_limits<Float>::radix == 2 &&
                std::numeric_limits<Float>::max_exponent == 128,
                int>::type
            )
        {
            return hash_binary((char*) &v, 4);
        }


        template <class T>
        inline std::size_t float_hash_impl2(T v)
        {
            boost::hash_detail::call_frexp<T> frexp;
            boost::hash_detail::call_ldexp<T> ldexp;

            int exp = 0;

            v = frexp(v, &exp);

            // A postive value is easier to hash, so combine the
            // sign with the exponent and use the absolute value.
            if(v < 0) {
                v = -v;
                exp += limits<T>::max_exponent -
                    limits<T>::min_exponent;
            }

            v = ldexp(v, limits<std::size_t>::digits);
            std::size_t seed = static_cast<std::size_t>(v);
            v -= static_cast<T>(seed);

            // ceiling(digits(T) * log2(radix(T))/ digits(size_t)) - 1;
            std::size_t const length
                = (limits<T>::digits *
                        boost::static_log2<limits<T>::radix>::value
                        + limits<std::size_t>::digits - 1)
                / limits<std::size_t>::digits;

            for(std::size_t i = 0; i != length; ++i)
            {
                v = ldexp(v, limits<std::size_t>::digits);
                std::size_t part = static_cast<std::size_t>(v);
                v -= static_cast<T>(part);
                hash_float_combine(seed, part);
            }

            hash_float_combine(seed, exp);

            return seed;
        }

        template <class T>
        inline bool is_zero(T v)
        {
#if !defined(__GNUC__)
            return v == 0;
#else
            // GCC's '-Wfloat-equal' will complain about comparing
            // v to 0, but because it disables warnings for system
            // headers it won't complain if you use std::equal_to to
            // compare with 0. Resulting in this silliness:
            return std::equal_to<T>()(v, 0);
#endif
        }


        template <class T>
        inline std::size_t float_hash_value(T v)
        {
            return boost::hash_detail::is_zero(v) ? 0 : float_hash_impl(v, 0);
        }


            inline operator float() const { return 0; }

            inline operator long double() const { return 0; }

            
            inline double operator()(double a, int b) const
            {
                using namespace std;
                return ldexp(a, b);
            }

            
            inline double operator()(double a, int* b) const
            {
                using namespace std;
                return frexp(a, b);
            }
                                   \
                                                                        \
            template <typename T>                                       \
            inline type1 operator()(type1 a, T b)  const                \
            {                                                           \
                using namespace std;                                    \
                return c99_func(a, b);                                  \
            }                                                           \
        };                                                              \
                                                                        \
        template <bool x>                                               \
        struct call_cpp_##c99_func :                                    \
            call_c99_##c99_func<                                        \
                ::boost::hash_detail::c99_func##_detect::check::c99     \
            > {};                                                       \
                                                                        \
        template <>                                                     \
        struct call_cpp_##c99_func<true> {                              \
            typedef type1 float_type;                                   \
                                                                        \
            template <typename T>                                       \
            inline type1 operator()(type1 a, T b)  const                \
            {                                                           \
                using namespace std;                                    \
                return cpp_func(a, b);                                  \
            }                                                           \
        };                                                              \
                                                                        \
        template <>                                                     \
        struct call_##cpp_func<type1> :                                 \
            call_cpp_##c99_func<                                        \
                ::boost::hash_detail::c99_func##_detect::check::cpp     \
            > {};                                                       \
    }                                                                   \
}

#define BOOST_HASH_CALL_FLOAT_MACRO(cpp_func, c99_func, type1, type2)   namespace boost {                                                       \
    namespace hash_detail {                                             \
                                                                        \
        template <>                                                     \
        struct call_##cpp_func<type1> {                                 \
            typedef type1 float_type;                                   \
            inline type1 operator()(type1 x, type2 y) const {           \
                return c99_func(x, y);                                  \
            }                                                           \
        };                                                              \
    }                                                                   \
}

#if defined(ldexpf)
BOOST_HASH_CALL_FLOAT_MACRO(ldexp, ldexpf, float, int)
#else
BOOST_HASH_CALL_FLOAT_FUNC(ldexp, ldexpf, float, int)
                                   \
                                                                        \
            template <typename T>                                       \
            inline type1 operator()(type1 a, T b)  const                \
            {                                                           \
                using namespace std;                                    \
                return cpp_func(a, b);                                  \
            }                                                           \
        };                                                              \
                                                                        \
        template <>                                                     \
        struct call_##cpp_func<type1> :                                 \
            call_cpp_##c99_func<                                        \
                ::boost::hash_detail::c99_func##_detect::check::cpp     \
            > {};                                                       \
    }                                                                   \
}

#define BOOST_HASH_CALL_FLOAT_MACRO(cpp_func, c99_func, type1, type2)   namespace boost {                                                       \
    namespace hash_detail {                                             \
                                                                        \
        template <>                                                     \
        struct call_##cpp_func<type1> {                                 \
            typedef type1 float_type;                                   \
            inline type1 operator()(type1 x, type2 y) const {           \
                return c99_func(x, y);                                  \
            }                                                           \
        };                                                              \
    }                                                                   \
}

#if defined(ldexpf)
BOOST_HASH_CALL_FLOAT_MACRO(ldexp, ldexpf, float, int)
#else
BOOST_HASH_CALL_FLOAT_FUNC(ldexp, ldexpf, float, int)
                                   \
                                                                        \
            template <typename T>                                       \
            inline type1 operator()(type1 a, T b)  const                \
            {                                                           \
                using namespace std;                                    \
                return c99_func(a, b);                                  \
            }                                                           \
        };                                                              \
                                                                        \
        template <bool x>                                               \
        struct call_cpp_##c99_func :                                    \
            call_c99_##c99_func<                                        \
                ::boost::hash_detail::c99_func##_detect::check::c99     \
            > {};                                                       \
                                                                        \
        template <>                                                     \
        struct call_cpp_##c99_func<true> {                              \
            typedef type1 float_type;                                   \
                                                                        \
            template <typename T>                                       \
            inline type1 operator()(type1 a, T b)  const                \
            {                                                           \
                using namespace std;                                    \
                return cpp_func(a, b);                                  \
            }                                                           \
        };                                                              \
                                                                        \
        template <>                                                     \
        struct call_##cpp_func<type1> :                                 \
            call_cpp_##c99_func<                                        \
                ::boost::hash_detail::c99_func##_detect::check::cpp     \
            > {};                                                       \
    }                                                                   \
}

#define BOOST_HASH_CALL_FLOAT_MACRO(cpp_func, c99_func, type1, type2)   namespace boost {                                                       \
    namespace hash_detail {                                             \
                                                                        \
        template <>                                                     \
        struct call_##cpp_func<type1> {                                 \
            typedef type1 float_type;                                   \
            inline type1 operator()(type1 x, type2 y) const {           \
                return c99_func(x, y);                                  \
            }                                                           \
        };                                                              \
    }                                                                   \
}

#if defined(ldexpf)
BOOST_HASH_CALL_FLOAT_MACRO(ldexp, ldexpf, float, int)
#else
BOOST_HASH_CALL_FLOAT_FUNC(ldexp, ldexpf, float, int)
#endif

#if defined(ldexpl)
BOOST_HASH_CALL_FLOAT_MACRO(ldexp, ldexpl, long double, int)
#else
BOOST_HASH_CALL_FLOAT_FUNC(ldexp, ldexpl, long double, int)
                                   \
                                                                        \
            template <typename T>                                       \
            inline type1 operator()(type1 a, T b)  const                \
            {                                                           \
                using namespace std;                                    \
                return cpp_func(a, b);                                  \
            }                                                           \
        };                                                              \
                                                                        \
        template <>                                                     \
        struct call_##cpp_func<type1> :                                 \
            call_cpp_##c99_func<                                        \
                ::boost::hash_detail::c99_func##_detect::check::cpp     \
            > {};                                                       \
    }                                                                   \
}

#define BOOST_HASH_CALL_FLOAT_MACRO(cpp_func, c99_func, type1, type2)   namespace boost {                                                       \
    namespace hash_detail {                                             \
                                                                        \
        template <>                                                     \
        struct call_##cpp_func<type1> {                                 \
            typedef type1 float_type;                                   \
            inline type1 operator()(type1 x, type2 y) const {           \
                return c99_func(x, y);                                  \
            }                                                           \
        };                                                              \
    }                                                                   \
}

#if defined(ldexpf)
BOOST_HASH_CALL_FLOAT_MACRO(ldexp, ldexpf, float, int)
#else
BOOST_HASH_CALL_FLOAT_FUNC(ldexp, ldexpf, float, int)
#endif

#if defined(ldexpl)
BOOST_HASH_CALL_FLOAT_MACRO(ldexp, ldexpl, long double, int)
#else
BOOST_HASH_CALL_FLOAT_FUNC(ldexp, ldexpl, long double, int)
                                   \
                                                                        \
            template <typename T>                                       \
            inline type1 operator()(type1 a, T b)  const                \
            {                                                           \
                using namespace std;                                    \
                return c99_func(a, b);                                  \
            }                                                           \
        };                                                              \
                                                                        \
        template <bool x>                                               \
        struct call_cpp_##c99_func :                                    \
            call_c99_##c99_func<                                        \
                ::boost::hash_detail::c99_func##_detect::check::c99     \
            > {};                                                       \
                                                                        \
        template <>                                                     \
        struct call_cpp_##c99_func<true> {                              \
            typedef type1 float_type;                                   \
                                                                        \
            template <typename T>                                       \
            inline type1 operator()(type1 a, T b)  const                \
            {                                                           \
                using namespace std;                                    \
                return cpp_func(a, b);                                  \
            }                                                           \
        };                                                              \
                                                                        \
        template <>                                                     \
        struct call_##cpp_func<type1> :                                 \
            call_cpp_##c99_func<                                        \
                ::boost::hash_detail::c99_func##_detect::check::cpp     \
            > {};                                                       \
    }                                                                   \
}

#define BOOST_HASH_CALL_FLOAT_MACRO(cpp_func, c99_func, type1, type2)   namespace boost {                                                       \
    namespace hash_detail {                                             \
                                                                        \
        template <>                                                     \
        struct call_##cpp_func<type1> {                                 \
            typedef type1 float_type;                                   \
            inline type1 operator()(type1 x, type2 y) const {           \
                return c99_func(x, y);                                  \
            }                                                           \
        };                                                              \
    }                                                                   \
}

#if defined(ldexpf)
BOOST_HASH_CALL_FLOAT_MACRO(ldexp, ldexpf, float, int)
#else
BOOST_HASH_CALL_FLOAT_FUNC(ldexp, ldexpf, float, int)
#endif

#if defined(ldexpl)
BOOST_HASH_CALL_FLOAT_MACRO(ldexp, ldexpl, long double, int)
#else
BOOST_HASH_CALL_FLOAT_FUNC(ldexp, ldexpl, long double, int)
#endif

#if defined(frexpf)
BOOST_HASH_CALL_FLOAT_MACRO(frexp, frexpf, float, int*)
#else
BOOST_HASH_CALL_FLOAT_FUNC(frexp, frexpf, float, int*)
                                   \
                                                                        \
            template <typename T>                                       \
            inline type1 operator()(type1 a, T b)  const                \
            {                                                           \
                using namespace std;                                    \
                return cpp_func(a, b);                                  \
            }                                                           \
        };                                                              \
                                                                        \
        template <>                                                     \
        struct call_##cpp_func<type1> :                                 \
            call_cpp_##c99_func<                                        \
                ::boost::hash_detail::c99_func##_detect::check::cpp     \
            > {};                                                       \
    }                                                                   \
}

#define BOOST_HASH_CALL_FLOAT_MACRO(cpp_func, c99_func, type1, type2)   namespace boost {                                                       \
    namespace hash_detail {                                             \
                                                                        \
        template <>                                                     \
        struct call_##cpp_func<type1> {                                 \
            typedef type1 float_type;                                   \
            inline type1 operator()(type1 x, type2 y) const {           \
                return c99_func(x, y);                                  \
            }                                                           \
        };                                                              \
    }                                                                   \
}

#if defined(ldexpf)
BOOST_HASH_CALL_FLOAT_MACRO(ldexp, ldexpf, float, int)
#else
BOOST_HASH_CALL_FLOAT_FUNC(ldexp, ldexpf, float, int)
#endif

#if defined(ldexpl)
BOOST_HASH_CALL_FLOAT_MACRO(ldexp, ldexpl, long double, int)
#else
BOOST_HASH_CALL_FLOAT_FUNC(ldexp, ldexpl, long double, int)
#endif

#if defined(frexpf)
BOOST_HASH_CALL_FLOAT_MACRO(frexp, frexpf, float, int*)
#else
BOOST_HASH_CALL_FLOAT_FUNC(frexp, frexpf, float, int*)
                                   \
                                                                        \
            template <typename T>                                       \
            inline type1 operator()(type1 a, T b)  const                \
            {                                                           \
                using namespace std;                                    \
                return c99_func(a, b);                                  \
            }                                                           \
        };                                                              \
                                                                        \
        template <bool x>                                               \
        struct call_cpp_##c99_func :                                    \
            call_c99_##c99_func<                                        \
                ::boost::hash_detail::c99_func##_detect::check::c99     \
            > {};                                                       \
                                                                        \
        template <>                                                     \
        struct call_cpp_##c99_func<true> {                              \
            typedef type1 float_type;                                   \
                                                                        \
            template <typename T>                                       \
            inline type1 operator()(type1 a, T b)  const                \
            {                                                           \
                using namespace std;                                    \
                return cpp_func(a, b);                                  \
            }                                                           \
        };                                                              \
                                                                        \
        template <>                                                     \
        struct call_##cpp_func<type1> :                                 \
            call_cpp_##c99_func<                                        \
                ::boost::hash_detail::c99_func##_detect::check::cpp     \
            > {};                                                       \
    }                                                                   \
}

#define BOOST_HASH_CALL_FLOAT_MACRO(cpp_func, c99_func, type1, type2)   namespace boost {                                                       \
    namespace hash_detail {                                             \
                                                                        \
        template <>                                                     \
        struct call_##cpp_func<type1> {                                 \
            typedef type1 float_type;                                   \
            inline type1 operator()(type1 x, type2 y) const {           \
                return c99_func(x, y);                                  \
            }                                                           \
        };                                                              \
    }                                                                   \
}

#if defined(ldexpf)
BOOST_HASH_CALL_FLOAT_MACRO(ldexp, ldexpf, float, int)
#else
BOOST_HASH_CALL_FLOAT_FUNC(ldexp, ldexpf, float, int)
#endif

#if defined(ldexpl)
BOOST_HASH_CALL_FLOAT_MACRO(ldexp, ldexpl, long double, int)
#else
BOOST_HASH_CALL_FLOAT_FUNC(ldexp, ldexpl, long double, int)
#endif

#if defined(frexpf)
BOOST_HASH_CALL_FLOAT_MACRO(frexp, frexpf, float, int*)
#else
BOOST_HASH_CALL_FLOAT_FUNC(frexp, frexpf, float, int*)
#endif

#if defined(frexpl)
BOOST_HASH_CALL_FLOAT_MACRO(frexp, frexpl, long double, int*)
#else
BOOST_HASH_CALL_FLOAT_FUNC(frexp, frexpl, long double, int*)
                                   \
                                                                        \
            template <typename T>                                       \
            inline type1 operator()(type1 a, T b)  const                \
            {                                                           \
                using namespace std;                                    \
                return cpp_func(a, b);                                  \
            }                                                           \
        };                                                              \
                                                                        \
        template <>                                                     \
        struct call_##cpp_func<type1> :                                 \
            call_cpp_##c99_func<                                        \
                ::boost::hash_detail::c99_func##_detect::check::cpp     \
            > {};                                                       \
    }                                                                   \
}

#define BOOST_HASH_CALL_FLOAT_MACRO(cpp_func, c99_func, type1, type2)   namespace boost {                                                       \
    namespace hash_detail {                                             \
                                                                        \
        template <>                                                     \
        struct call_##cpp_func<type1> {                                 \
            typedef type1 float_type;                                   \
            inline type1 operator()(type1 x, type2 y) const {           \
                return c99_func(x, y);                                  \
            }                                                           \
        };                                                              \
    }                                                                   \
}

#if defined(ldexpf)
BOOST_HASH_CALL_FLOAT_MACRO(ldexp, ldexpf, float, int)
#else
BOOST_HASH_CALL_FLOAT_FUNC(ldexp, ldexpf, float, int)
#endif

#if defined(ldexpl)
BOOST_HASH_CALL_FLOAT_MACRO(ldexp, ldexpl, long double, int)
#else
BOOST_HASH_CALL_FLOAT_FUNC(ldexp, ldexpl, long double, int)
#endif

#if defined(frexpf)
BOOST_HASH_CALL_FLOAT_MACRO(frexp, frexpf, float, int*)
#else
BOOST_HASH_CALL_FLOAT_FUNC(frexp, frexpf, float, int*)
#endif

#if defined(frexpl)
BOOST_HASH_CALL_FLOAT_MACRO(frexp, frexpl, long double, int*)
#else
BOOST_HASH_CALL_FLOAT_FUNC(frexp, frexpl, long double, int*)
