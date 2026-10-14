/* Helpers the PC's compiler calls from Native code on 32-bit x86 that the host's C runtime
 * does not provide under these names (they come from libgcc / compiler-rt elsewhere). */
#include <stdint.h>

uint64_t __udivdi3(uint64_t a, uint64_t b);
uint64_t __umoddi3(uint64_t a, uint64_t b);
int64_t __divdi3(int64_t a, int64_t b);
int64_t __moddi3(int64_t a, int64_t b);

uint64_t __udivdi3(uint64_t a, uint64_t b) { return a / b; }
uint64_t __umoddi3(uint64_t a, uint64_t b) { return a % b; }
int64_t __divdi3(int64_t a, int64_t b) { return a / b; }
int64_t __moddi3(int64_t a, int64_t b) { return a % b; }
