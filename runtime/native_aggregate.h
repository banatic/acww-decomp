/* Audited aggregate return boundaries. NativeFunction.host keeps the PC ABI;
 * only interpreter crossings use these conversions. */
#ifndef RUNTIME_NATIVE_AGGREGATE_H
#define RUNTIME_NATIVE_AGGREGATE_H

#include <stdint.h>
#include "native_table.h"

typedef struct NativeAggregateCall {
    uint32_t storage[2];
    void *output;
    int hidden;
} NativeAggregateCall;

static inline int native_aggregate_kind(int kind)
{
    return kind >= NATIVE_RET_STRUCT3 && kind <= NATIVE_RET_STRUCT4;
}

uint64_t native_aggregate_invoke(int kind, const void *function, const uint32_t *arm);
void native_aggregate_prepare(int kind, const uint32_t *pc, uint32_t *arm, NativeAggregateCall *call);
uint64_t native_aggregate_finish(int kind, NativeAggregateCall *call, uint64_t registers, uint32_t *pop_bytes);
/* The sole differing Clean ABI is the resident 020404b4 union/scalar pair. */
const void *native_aggregate_clean_bridge(int from, int to, const void *function);

#endif
