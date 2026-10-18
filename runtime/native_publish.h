#ifndef NATIVE_PUBLISH_H
#define NATIVE_PUBLISH_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* A PC copy supplies its computed value. Replay supplies timing, never data. */
extern void (*native_publish_hook)(uint32_t pc, uint32_t *address, uint32_t value);
void native_publish_word(uint32_t pc, uint32_t *address, uint32_t value);

#ifdef __cplusplus
}
#endif

#endif
