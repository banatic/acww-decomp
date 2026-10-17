#ifndef NATIVE_GUEST_H
#define NATIVE_GUEST_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Install both hooks together, before entering Native code. The enter hook
 * saves the real return PC per execution context. The return hook restores it
 * and must use only integer registers (an x87 result may still be live).
 * Indices first identify native_functions, then clean_functions, including
 * their overlay. Both tables have stable, distinct entry identities. */
extern void (*native_guest_enter_hook)(uint32_t index, uintptr_t caller, const uint32_t *args);
extern uintptr_t (*native_guest_return_hook)(uint32_t index);
extern uint32_t (*native_guest_slot_hook)(uint32_t owner, uint32_t offset, uint32_t size);
void native_guest_enter(uint32_t index, uintptr_t caller, const uint32_t *args);
__attribute__((target("general-regs-only"))) uintptr_t native_guest_return(uint32_t index);
uint32_t native_guest_stack_slot(uint32_t owner, uint32_t offset, uint32_t size);

#ifdef __cplusplus
}
#endif

#endif
