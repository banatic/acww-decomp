/* func_020ea48c @ 0x020ea48c, 0x80 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

extern u32 data_021fbe90;
extern u32 data_021fbe98;

extern void *OS_GetArenaLo(u32 id);
extern void *OS_GetArenaHi(u32 id);
extern void *OS_AllocFromArenaLo(u32 id, u32 size, u32 align);
extern void *func_020ea50c(void *ptr, u32 size);
extern void *func_020ea550(void);

void func_020ea48c(void)
{
    u32 configured_size;
    u32 size;

    configured_size = data_021fbe90;
    data_021fbe98 = 0;
    size = *(volatile u32 *) &data_021fbe90;
    if (configured_size == 0) {
        u32 lo = (u32) OS_GetArenaLo(0);
        u32 hi = (u32) OS_GetArenaHi(data_021fbe98);
        size = hi - ((lo + 0x1f) & ~0x1f);
    }

    if (func_020ea50c(OS_AllocFromArenaLo(data_021fbe98, size, 0x20), size) != 0) {
        func_020ea550();
    }
}
