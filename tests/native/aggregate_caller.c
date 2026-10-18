/* Compiled with the Native compiler, independently of the runtime compiler. */
#include <stdint.h>
#include <string.h>
#include "native_table.h"

typedef struct {
    unsigned char a, b, c;
} Three;
typedef struct {
    unsigned char a, b, c, d;
} Four;
typedef union {
    uint32_t word;
    Four bytes;
} Word;
typedef struct {
    uint32_t first, second;
} Pair;

uint32_t aggregate_scalar_caller(uint32_t target, const uint32_t *args)
{
    return ((uint32_t (*)(uint32_t, uint32_t, uint32_t))(uintptr_t) target)(args[0], args[1], args[2]);
}

uint64_t aggregate_pc_caller(int kind, uint32_t target, const uint32_t *args)
{
    switch (kind) {
        case NATIVE_RET_STRUCT3: {
            Three value = ((Three (*)(uint32_t, uint32_t))(uintptr_t) target)(args[0], args[1]);
            return value.a | ((uint32_t) value.b << 8) | ((uint32_t) value.c << 16);
        }
        case NATIVE_RET_UNION4: {
            Four argument;
            memcpy(&argument, &args[2], 4);
            Word value = ((Word (*)(uint32_t, uint32_t, Four))(uintptr_t) target)(args[0], args[1], argument);
            return value.word;
        }
        case NATIVE_RET_PAIR8: {
            Pair value = ((Pair (*)(uint32_t, uint32_t))(uintptr_t) target)(args[1], args[2]);
            return ((uint64_t) value.second << 32) | value.first;
        }
        case NATIVE_RET_STRUCT4: {
            Four value = ((Four (*)(uint32_t))(uintptr_t) target)(args[0]);
            uint32_t word;
            memcpy(&word, &value, 4);
            return word;
        }
    }
    return UINT64_MAX;
}
