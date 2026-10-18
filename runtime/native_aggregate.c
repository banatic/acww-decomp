#include "native_aggregate.h"

#include <stdlib.h>
#include <string.h>
#include "io.h"

/* These C layouts deliberately have the original fields' size and alignment.
 * The host compiler supplies its own hidden result pointer and stack cleanup.
 * The runtime's and Native C compilers use the same i386 aggregate ABI. */
typedef struct {
    unsigned char bytes[3];
} Bytes3;
typedef struct {
    unsigned char bytes[4];
} Bytes4;
typedef union {
    uint32_t word;
    unsigned char bytes[4];
} Word4;
typedef struct {
    uint32_t first, second;
} Pair8;
_Static_assert(sizeof(Bytes3) == 3 && _Alignof(Bytes3) == 1, "three-byte PC result");
_Static_assert(sizeof(Bytes4) == 4 && _Alignof(Bytes4) == 1, "four-byte PC aggregate");
_Static_assert(sizeof(Word4) == 4 && _Alignof(Word4) == 4, "four-byte PC union");
_Static_assert(sizeof(Pair8) == 8 && _Alignof(Pair8) == 4, "eight-byte PC pair");

static const void *union_to_scalar_target, *scalar_to_union_target;

static Word4 union_to_scalar(uint32_t object, uint32_t event, Bytes4 date)
{
    uint32_t word;
    memcpy(&word, &date, 4);
    Word4 result;
    result.word = ((uint32_t (*)(uint32_t, uint32_t, uint32_t)) union_to_scalar_target)(object, event, word);
    return result;
}

static uint32_t scalar_to_union(uint32_t object, uint32_t event, uint32_t word)
{
    Bytes4 date;
    memcpy(&date, &word, 4);
    Word4 result = ((Word4 (*)(uint32_t, uint32_t, Bytes4)) scalar_to_union_target)(object, event, date);
    return result.word;
}

const void *native_aggregate_clean_bridge(int from, int to, const void *function)
{
    if (from == NATIVE_RET_UNION4 && to == NATIVE_RET_32) {
        union_to_scalar_target = function;
        return union_to_scalar;
    }
    if (from == NATIVE_RET_32 && to == NATIVE_RET_UNION4) {
        scalar_to_union_target = function;
        return scalar_to_union;
    }
    abort();
}

uint64_t native_aggregate_invoke(int kind, const void *function, const uint32_t *arm)
{
    switch (kind) {
        case NATIVE_RET_STRUCT3: {
            Bytes3 result = ((Bytes3 (*)(uint32_t, uint32_t)) function)(arm[0], arm[1]);
            return result.bytes[1] | ((uint32_t) result.bytes[0] << 8) | ((uint32_t) result.bytes[2] << 16);
        }
        case NATIVE_RET_UNION4: {
            Bytes4 argument;
            memcpy(&argument, &arm[2], 4);
            Word4 result = ((Word4 (*)(uint32_t, uint32_t, Bytes4)) function)(arm[0], arm[1], argument);
            return result.word;
        }
        case NATIVE_RET_PAIR8: {
            Pair8 result = ((Pair8 (*)(uint32_t, uint32_t)) function)(arm[1], arm[2]);
            if (!bus_write(arm[0], 4, result.first) || !bus_write(arm[0] + 4, 4, result.second)) {
                abort();
            }
            return ((uint64_t) result.first << 32) | result.second;
        }
        case NATIVE_RET_STRUCT4: {
            Bytes4 result = ((Bytes4 (*)(uint32_t)) function)(arm[0]);
            uint32_t word;
            memcpy(&word, &result, 4);
            return word;
        }
        default:
            abort();
    }
}

void native_aggregate_prepare(int kind, const uint32_t *pc, uint32_t *arm, NativeAggregateCall *call)
{
    if (!native_aggregate_kind(kind)) {
        abort();
    }
#ifdef _WIN32
    call->hidden = kind == NATIVE_RET_STRUCT3;
#else
    call->hidden = 1;
#endif
    call->output = call->hidden ? (void *) (uintptr_t) pc[0] : call->storage;
    unsigned start = (unsigned) call->hidden;
    if (kind == NATIVE_RET_PAIR8) {
        arm[0] = (uint32_t) (uintptr_t) call->output;
        arm[1] = pc[start];
        arm[2] = pc[start + 1];
    } else {
        unsigned count = kind == NATIVE_RET_STRUCT3 ? 2 : kind == NATIVE_RET_UNION4 ? 3 : 1;
        memmove(arm, pc + start, count * 4);
    }
}

uint64_t native_aggregate_finish(int kind, NativeAggregateCall *call, uint64_t registers, uint32_t *pop_bytes)
{
    if (!native_aggregate_kind(kind)) {
        abort();
    }
    *pop_bytes = 0;
#ifndef _WIN32
    *pop_bytes = call->hidden ? 4 : 0;
#endif
    uint32_t result = (uint32_t) registers;
    if (kind == NATIVE_RET_PAIR8) {
        /* ARM has already written the result through its hidden pointer. */
        if (call->hidden) {
            return (uint32_t) (uintptr_t) call->output;
        }
        return ((uint64_t) call->storage[1] << 32) | call->storage[0];
    }
    if (call->hidden) {
        if (kind == NATIVE_RET_STRUCT3) {
            unsigned char bytes[3] = {(unsigned char) (result >> 8), (unsigned char) result, (unsigned char) (result >> 16)};
            memcpy(call->output, bytes, 3);
        } else {
            memcpy(call->output, &result, 4);
        }
        return (uint32_t) (uintptr_t) call->output;
    }
    return result;
}
