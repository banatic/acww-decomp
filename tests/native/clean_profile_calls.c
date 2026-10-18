/* Reuse the ABI tests with public Clean aliases and absolute function pointers. */
#define main profile_basic_main
#include "profile_calls.c"
#undef main

#ifdef PROFILE_BODIES
void *clean_entry_address(void)
{
    return (void *) probe_args;
}

uint32_t clean_call_pointer(uint32_t n)
{
    uint32_t (*volatile call)(uint32_t) = probe_recurse;
    return call(n);
}
#else
#include "native_table.h"
extern void *clean_entry_address(void);
extern uint32_t clean_call_pointer(uint32_t);
extern uint32_t native_probe_tail_target(uint32_t);
extern const NativeBody clean_bodies[];
extern const uint32_t clean_body_count;

int main(void)
{
    assert((uintptr_t) clean_entry_address() == (uintptr_t) native_probe_args);
    assert(clean_call_pointer(6) == 28);
    const void *expected[] = {(const void *) native_probe_args,     (const void *) native_probe_wide,
                              (const void *) native_probe_void,     (const void *) native_probe_signed,
                              (const void *) native_probe_unsigned, (const void *) native_probe_double,
                              (const void *) native_probe_struct,   (const void *) native_probe_recurse,
                              (const void *) native_probe_tail,     (const void *) native_probe_tail_target};
    assert(clean_body_count == 10);
    for (unsigned i = 0; i < clean_body_count; ++i) {
        assert(clean_bodies[i].wrapper == expected[i]);
        assert(clean_bodies[i].body != 0 && clean_bodies[i].body != clean_bodies[i].wrapper);
    }
    int result = profile_basic_main();
    native_guest_return_hook = leave;
    native_guest_enter_hook = enter;
    assert(clean_call_pointer(6) == 28);
    assert(depth == 0 && entries == 16007 && exits == entries && calls[7] == 7007);
#ifdef PROFILE_SIGNAL_CHECK
    assert(signals == 16007);
#endif
    native_guest_enter_hook = 0;
    native_guest_return_hook = 0;
    puts("Clean aliases preserve direct calls, absolute function pointers and body mappings");
    return result;
}
#endif
