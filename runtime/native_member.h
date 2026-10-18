/* ARM member pointers in shared game memory. Included only by verified PC copies.
 * Keep this an aggregate with trivial copying: interpreted callers pass two words,
 * and the ROM's tables must never acquire host member-pointer encodings. */
#ifndef RUNTIME_NATIVE_MEMBER_H
#define RUNTIME_NATIVE_MEMBER_H

/* Scalar results use the host callable ABI. An audited source with an ARM
 * hidden result pointer supplies a specialization before instantiating its
 * member type; it must not rely on the host's aggregate return convention. */
template <class Class, class Result, class... Args> struct NativeMemberCall {
    static Result invoke(unsigned int function, Class *object, Args... args)
    {
        static_assert(!__is_class(Result) && !__is_union(Result), "ARM aggregate result needs an audited adapter");
        return reinterpret_cast<Result (*)(Class *, Args...)>(function)(object, args...);
    }
};

template <class Class, class Result, class... Args> struct NativeMember {
    unsigned int function;
    int adjustment; /* twice the signed this offset, plus the virtual flag */

    struct Bound {
        unsigned int function;
        Class *object;

        Result operator()(Args... args) const
        {
            return NativeMemberCall<Class, Result, Args...>::invoke(function, object, args...);
        }
    };

    /* The verified mwccarm call sites test the first word alone, including for a
     * virtual pointer with slot zero. Do not substitute the host ABI's null test. */
    explicit operator bool() const
    {
        return function != 0;
    }
    bool operator==(decltype(nullptr)) const
    {
        return function == 0;
    }
    bool operator!=(decltype(nullptr)) const
    {
        return function != 0;
    }

    Bound bind(Class *object) const
    {
        static_assert(sizeof(void *) == 4 && sizeof(int) == 4, "32-bit Native ABI required");
        static_assert((-1 >> 1) == -1, "signed ARM adjustment needs arithmetic shift");
        Class *adjusted = reinterpret_cast<Class *>(reinterpret_cast<char *>(object) + (adjustment >> 1));
        unsigned int target = function;
        if (adjustment & 1) {
            unsigned int vtable = *reinterpret_cast<const unsigned int *>(adjusted);
            target = *reinterpret_cast<const unsigned int *>(vtable + function);
        }
        /* A direct Thumb target stays odd. The existing Native fault dispatcher
         * resolves DS code addresses; this value is never a host member pointer. */
        return Bound{target, adjusted};
    }
};

template <class Object, class Class, class Result, class... Args>
typename NativeMember<Class, Result, Args...>::Bound operator->*(Object *object, NativeMember<Class, Result, Args...> member)
{
    return member.bind(static_cast<Class *>(object));
}

#endif
