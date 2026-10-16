/* C++ pointers to member functions as the game's compiler (mwcc for ARM) lays them out, and
 * the tables of them the state machines in this overlay dispatch through.
 *
 * Such a table is a function-local static: the compiler fills it from constants in the
 * overlay's data the first time the function runs, and records that in bit 0 of a guard word.
 * Both are in the overlay's .bss, so the copy is part of what the function writes. */
#ifndef CLEAN_OV004_MEMBER_POINTER_H
#define CLEAN_OV004_MEMBER_POINTER_H

#include <stdint.h>

#include "types.h"

typedef struct MemberPointer {
    u32 function; /* the function's address, or for a virtual one its offset in the vtable */
    s32 adjust;   /* twice the offset added to the object, plus 1 when the function is virtual */
} MemberPointer;

/* The table filled from `count` constants, once (bit 0 of `guard` says it was). */
static inline void MemberTable_InitOnce(u32 *guard, MemberPointer *table, const MemberPointer *const *constants, int count)
{
    u32 flags = *guard;
    if ((flags & 1) == 0) {
        for (int i = 0; i < count; i++) {
            table[i] = *constants[i];
        }
        *guard = flags | 1;
    }
}

/* The object a member pointer is called with, and the address of the code it calls. */
static inline void *MemberPointer_Object(const MemberPointer *member, void *object)
{
    /* the offset is a whole number of bytes: adjust minus its low bit is even */
    return (u8 *) object + (member->adjust - (member->adjust & 1)) / 2;
}

static inline u32 MemberPointer_Code(const MemberPointer *member, void *adjusted)
{
    if (member->adjust & 1) {
        const u8 *vtable = *(const u8 *const *) adjusted;
        return *(const u32 *) (vtable + member->function);
    }
    return member->function;
}

/* Calls through a member pointer whose function takes nothing and returns nothing, or an int. */
static inline void MemberPointer_CallVoid(const MemberPointer *member, void *object)
{
    void *self = MemberPointer_Object(member, object);
    ((void (*)(void *))(uintptr_t) MemberPointer_Code(member, self))(self);
}

static inline int MemberPointer_CallInt(const MemberPointer *member, void *object)
{
    void *self = MemberPointer_Object(member, object);
    return ((int (*)(void *))(uintptr_t) MemberPointer_Code(member, self))(self);
}

#endif
