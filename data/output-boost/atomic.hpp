
inline void atomic_thread_fence(memory_order)
{
}

inline void atomic_signal_fence(memory_order order)
{
    atomic_thread_fence(order);
}


inline void
ppc_fence_before(memory_order order)
{
    switch(order) {
        case memory_order_release:
        case memory_order_acq_rel:
#if defined(__powerpc64__)
            __asm__ __volatile__ ("lwsync" ::: "memory");
            break;
#endif
        case memory_order_seq_cst:
            __asm__ __volatile__ ("sync" ::: "memory");
        default:;
    }
}


inline void
ppc_fence_after(memory_order order)
{
    switch(order) {
        case memory_order_acquire:
        case memory_order_acq_rel:
        case memory_order_seq_cst:
            __asm__ __volatile__ ("isync");
        case memory_order_consume:
            __asm__ __volatile__ ("" ::: "memory");
        default:;
    }
}


inline void
ppc_fence_after_store(memory_order order)
{
    switch(order) {
        case memory_order_seq_cst:
            __asm__ __volatile__ ("sync");
        default:;
    }
}

inline void
atomic_thread_fence(memory_order order)
{
    switch(order) {
        case memory_order_acquire:
            __asm__ __volatile__ ("isync" ::: "memory");
            break;
        case memory_order_release:
#if defined(__powerpc64__)
            __asm__ __volatile__ ("lwsync" ::: "memory");
            break;
#endif
        case memory_order_acq_rel:
        case memory_order_seq_cst:
            __asm__ __volatile__ ("sync" ::: "memory");
        default:;
    }
}

inline void
atomic_signal_fence(memory_order order)
{
    switch(order) {
        case memory_order_acquire:
        case memory_order_release:
        case memory_order_acq_rel:
        case memory_order_seq_cst:
            __asm__ __volatile__ ("" ::: "memory");
            break;
        default:;
    }
}


inline void
arm_barrier(void)
{
    void (*kernel_dmb)(void) = (void (*)(void)) 0xffff0fa0;
    kernel_dmb();
}


inline void
platform_fence_before(memory_order order)
{
    switch(order) {
        case memory_order_release:
        case memory_order_acq_rel:
        case memory_order_seq_cst:
            arm_barrier();
        case memory_order_consume:
        default:;
    }
}


inline void
platform_fence_after(memory_order order)
{
    switch(order) {
        case memory_order_acquire:
        case memory_order_acq_rel:
        case memory_order_seq_cst:
            arm_barrier();
        default:;
    }
}


inline void
platform_fence_before_store(memory_order order)
{
    platform_fence_before(order);
}


inline void
platform_fence_after_store(memory_order order)
{
    if (order == memory_order_seq_cst)
        arm_barrier();
}


inline void
platform_fence_after_load(memory_order order)
{
    platform_fence_after(order);
}


template<typename T>
inline bool
platform_cmpxchg32(T & expected, T desired, volatile T * ptr)
{
    typedef T (*kernel_cmpxchg32_t)(T oldval, T newval, volatile T * ptr);

    if (((kernel_cmpxchg32_t) 0xffff0fc0)(expected, desired, ptr) == 0) {
        return true;
    } else {
        expected = *ptr;
        return false;
    }
}

inline void
atomic_thread_fence(memory_order order)
{
    switch(order) {
        case memory_order_acquire:
        case memory_order_release:
        case memory_order_acq_rel:
        case memory_order_seq_cst:
            atomics::detail::arm_barrier();
        default:;
    }
}

inline void
atomic_signal_fence(memory_order)
{
    __asm__ __volatile__ ("" ::: "memory");
}


inline void
platform_fence_before(memory_order order)
{
    switch(order)
    {
    case memory_order_relaxed:
    case memory_order_acquire:
    case memory_order_consume:
        break;
    case memory_order_release:
    case memory_order_acq_rel:
        __asm__ __volatile__ ("" ::: "memory");
        /* release */
        break;
    case memory_order_seq_cst:
        __asm__ __volatile__ ("" ::: "memory");
        /* seq */
        break;
    default:;
    }
}


inline void
platform_fence_after(memory_order order)
{
    switch(order)
    {
    case memory_order_relaxed:
    case memory_order_release:
        break;
    case memory_order_acquire:
    case memory_order_acq_rel:
        __asm__ __volatile__ ("" ::: "memory");
        /* acquire */
        break;
    case memory_order_consume:
        /* consume */
        break;
    case memory_order_seq_cst:
        __asm__ __volatile__ ("" ::: "memory");
        /* seq */
        break;
    default:;
    }
}


inline void
platform_fence_after_load(memory_order order)
{
    switch(order)
    {
    case memory_order_relaxed:
    case memory_order_release:
        break;
    case memory_order_acquire:
    case memory_order_acq_rel:
        __asm__ __volatile__ ("" ::: "memory");
        break;
    case memory_order_consume:
        break;
    case memory_order_seq_cst:
        __asm__ __volatile__ ("" ::: "memory");
        break;
    default:;
    }
}


inline void
platform_fence_before_store(memory_order order)
{
    switch(order)
    {
    case memory_order_relaxed:
    case memory_order_acquire:
    case memory_order_consume:
        break;
    case memory_order_release:
    case memory_order_acq_rel:
        __asm__ __volatile__ ("" ::: "memory");
        /* release */
        break;
    case memory_order_seq_cst:
        __asm__ __volatile__ ("" ::: "memory");
        /* seq */
        break;
    default:;
    }
}


inline void
platform_fence_after_store(memory_order order)
{
    switch(order)
    {
    case memory_order_relaxed:
    case memory_order_release:
        break;
    case memory_order_acquire:
    case memory_order_acq_rel:
        __asm__ __volatile__ ("" ::: "memory");
        /* acquire */
        break;
    case memory_order_consume:
        /* consume */
        break;
    case memory_order_seq_cst:
        __asm__ __volatile__ ("" ::: "memory");
        /* seq */
        break;
    default:;
    }
}

inline void
atomic_thread_fence(memory_order order)
{
    switch(order)
    {
    case memory_order_relaxed:
        break;
    case memory_order_release:
        __asm__ __volatile__ ("" ::: "memory");
        break;
    case memory_order_acquire:
        __asm__ __volatile__ ("" ::: "memory");
        break;
    case memory_order_acq_rel:
        __asm__ __volatile__ ("" ::: "memory");
        break;
    case memory_order_consume:
        break;
    case memory_order_seq_cst:
        __asm__ __volatile__ (BOOST_ATOMIC_X86_FENCE_INSTR ::: "memory");
        break;
    default:;
    }
}

inline void
atomic_signal_fence(memory_order)
{
    __asm__ __volatile__ ("" ::: "memory");
}


inline void
arm_barrier(void)
{
    int brtmp;
    __asm__ __volatile__ (
        BOOST_ATOMIC_ARM_ASM_START(%0)
        BOOST_ATOMIC_ARM_DMB
        BOOST_ATOMIC_ARM_ASM_END(%0)
        : "=&l" (brtmp) :: "memory"
    );
}


inline void
platform_fence_before(memory_order order)
{
    switch(order) {
        case memory_order_release:
        case memory_order_acq_rel:
        case memory_order_seq_cst:
            arm_barrier();
        case memory_order_consume:
        default:;
    }
}


inline void
platform_fence_after(memory_order order)
{
    switch(order) {
        case memory_order_acquire:
        case memory_order_acq_rel:
        case memory_order_seq_cst:
            arm_barrier();
        default:;
    }
}


inline void
platform_fence_before_store(memory_order order)
{
    platform_fence_before(order);
}


inline void
platform_fence_after_store(memory_order order)
{
    if (order == memory_order_seq_cst)
        arm_barrier();
}


inline void
platform_fence_after_load(memory_order order)
{
    platform_fence_after(order);
}


template<typename T>
inline bool
platform_cmpxchg32(T & expected, T desired, volatile T * ptr)
{
    int success;
    int tmp;
    __asm__ (
        BOOST_ATOMIC_ARM_ASM_START(%2)
        "mov     %1, #0\n"        // success = 0
        "ldrex   %0, %3\n"      // expected' = *(&i)
        "teq     %0, %4\n"        // flags = expected'==expected
        "ittt    eq\n"
        "strexeq %2, %5, %3\n"  // if (flags.equal) *(&i) = desired, tmp = !OK
        "teqeq   %2, #0\n"        // if (flags.equal) flags = tmp==0
        "moveq   %1, #1\n"        // if (flags.equal) success = 1
        BOOST_ATOMIC_ARM_ASM_END(%2)
            : "=&r" (expected),  // %0
            "=&r" (success),   // %1
            "=&l" (tmp),       // %2
            "+Q" (*ptr)          // %3
            : "r" (expected),    // %4
            "r" (desired) // %5
            : "cc"
        );
    return success;
}

inline void
atomic_thread_fence(memory_order order)
{
    switch(order) {
        case memory_order_acquire:
        case memory_order_release:
        case memory_order_acq_rel:
        case memory_order_seq_cst:
            atomics::detail::arm_barrier();
        default:;
    }
}

inline void
atomic_signal_fence(memory_order)
{
    __asm__ __volatile__ ("" ::: "memory");
}


inline memory_order
calculate_failure_order(memory_order order)
{
    switch(order) {
        case memory_order_acq_rel:
            return memory_order_acquire;
        case memory_order_release:
            return memory_order_relaxed;
        default:
            return order;
    }
}

    base_atomic(void) {}


inline void
platform_fence_before(memory_order order)
{
    switch(order) {
        case memory_order_relaxed:
        case memory_order_acquire:
        case memory_order_consume:
            break;
        case memory_order_release:
        case memory_order_acq_rel:
            __asm__ __volatile__ ("membar #StoreStore | #LoadStore" ::: "memory");
            /* release */
            break;
        case memory_order_seq_cst:
            __asm__ __volatile__ ("membar #Sync" ::: "memory");
            /* seq */
            break;
    }
}


inline void
platform_fence_after(memory_order order)
{
    switch(order) {
        case memory_order_relaxed:
        case memory_order_release:
            break;
        case memory_order_acquire:
        case memory_order_acq_rel:
            __asm__ __volatile__ ("membar #LoadLoad | #LoadStore" ::: "memory");
            /* acquire */
            break;
        case memory_order_consume:
            /* consume */
            break;
        case memory_order_seq_cst:
            __asm__ __volatile__ ("membar #Sync" ::: "memory");
            /* seq */
            break;
        default:;
    }
}


inline void
platform_fence_after_store(memory_order order)
{
    switch(order) {
        case memory_order_seq_cst:
            __asm__ __volatile__ ("membar #Sync" ::: "memory");
        default:;
    }
}



inline void
platform_fence_after_load(memory_order order)
{
    platform_fence_after(order);
}

inline void
atomic_thread_fence(memory_order order)
{
    switch(order) {
        case memory_order_relaxed:
            break;
        case memory_order_release:
            __asm__ __volatile__ ("membar #StoreStore | #LoadStore" ::: "memory");
            break;
        case memory_order_acquire:
            __asm__ __volatile__ ("membar #LoadLoad | #LoadStore" ::: "memory");
            break;
        case memory_order_acq_rel:
            __asm__ __volatile__ ("membar #LoadLoad | #LoadStore | #StoreStore" ::: "memory");
            break;
        case memory_order_consume:
            break;
        case memory_order_seq_cst:
            __asm__ __volatile__ ("membar #Sync" ::: "memory");
            break;
        default:;
    }
}

inline void
atomic_signal_fence(memory_order)
{
    __asm__ __volatile__ ("" ::: "memory");
}

inline void
atomic_thread_fence(memory_order order)
{
    switch(order) {
        case memory_order_relaxed:
            break;
        case memory_order_release:
        case memory_order_consume:
        case memory_order_acquire:
        case memory_order_acq_rel:
        case memory_order_seq_cst:
            __sync_synchronize();
            break;
    }
}


inline void
platform_fence_before(memory_order)
{
    /* empty, as compare_and_swap is synchronizing already */
}


inline void
platform_fence_after(memory_order)
{
    /* empty, as compare_and_swap is synchronizing already */
}


inline void
platform_fence_before_store(memory_order order)
{
    switch(order) {
        case memory_order_relaxed:
        case memory_order_acquire:
        case memory_order_consume:
            break;
        case memory_order_release:
        case memory_order_acq_rel:
        case memory_order_seq_cst:
            __sync_synchronize();
            break;
    }
}


inline void
platform_fence_after_store(memory_order order)
{
    if (order == memory_order_seq_cst)
        __sync_synchronize();
}


inline void
platform_fence_after_load(memory_order order)
{
    switch(order) {
        case memory_order_relaxed:
        case memory_order_release:
            break;
        case memory_order_consume:
        case memory_order_acquire:
        case memory_order_acq_rel:
        case memory_order_seq_cst:
            __sync_synchronize();
            break;
    }
}


template<typename T>
inline bool
platform_cmpxchg32_strong(T & expected, T desired, volatile T * ptr)
{
    T found = __sync_val_compare_and_swap(ptr, expected, desired);
    bool success = (found == expected);
    expected = found;
    return success;
}


inline void fence_before(memory_order order)
{
    switch(order) {
        case memory_order_consume:
        case memory_order_release:
        case memory_order_acq_rel:
        case memory_order_seq_cst:
            __asm__ __volatile__ ("mb" ::: "memory");
        default:;
    }
}


inline void fence_after(memory_order order)
{
    switch(order) {
        case memory_order_acquire:
        case memory_order_acq_rel:
        case memory_order_seq_cst:
            __asm__ __volatile__ ("mb" ::: "memory");
        default:;
    }
}


template<>
inline void platform_atomic_thread_fence(memory_order order)
{
    switch(order) {
        case memory_order_acquire:
        case memory_order_consume:
        case memory_order_release:
        case memory_order_acq_rel:
        case memory_order_seq_cst:
            __asm__ __volatile__ ("mb" ::: "memory");
        default:;
    }
}

        explicit
        scoped_lock(const volatile void * addr) : mtx_(get_lock_for(addr))
        {
            mtx_.lock();
        }

        ~scoped_lock()
        {
            mtx_.unlock();
        }

    inline int32_t
    fenced_compare_exchange_strong_32(volatile int32_t *ptr, int32_t expected, int32_t desired)
    {
        return __sync_val_compare_and_swap_4(ptr, expected, desired);
    }

    inline int64_t
    fenced_compare_exchange_strong_64(int64_t *ptr, int64_t expected, int64_t desired)
    {
        return __sync_val_compare_and_swap_8(ptr, expected, desired);
    }

    explicit atomic_generic_cas32(T v) : i((int32_t)v) {}

    atomic_generic_cas32() {}

    T load(memory_order order=memory_order_seq_cst) const volatile
    {
        T expected=(T)i;
        do { } while(!const_cast<this_type *>(this)->compare_exchange_weak(expected, expected, order, memory_order_relaxed));
        return expected;
    }

    void store(T v, memory_order order=memory_order_seq_cst) volatile
    {
        exchange(v);
    }

    bool compare_exchange_strong(
        T &expected,
        T desired,
        memory_order success_order,
        memory_order failure_order) volatile
    {
        T found;
        found=(T)fenced_compare_exchange_strong_32(&i, (int32_t)expected, (int32_t)desired);
        bool success=(found==expected);
        expected=found;
        return success;
    }

    bool compare_exchange_weak(
        T &expected,
        T desired,
        memory_order success_order,
        memory_order failure_order) volatile
    {
        return compare_exchange_strong(expected, desired, success_order, failure_order);
    }

    T exchange(T r, memory_order order=memory_order_seq_cst) volatile
    {
        T expected=(T)i;
        do { } while(!compare_exchange_weak(expected, r, order, memory_order_relaxed));
        return expected;
    }


    bool is_lock_free(void) const volatile {return true;}

    explicit platform_atomic_integral(T v) : super(v) {}

    platform_atomic_integral(void) {}
