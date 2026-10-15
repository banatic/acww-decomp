/* func_0205e8f8 @ 0x0205e8f8, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u32 data_021ca16c[];
extern u16 *func_0205f100(u32 *t, u8 k);
extern void *func_0205f130(u32 *t, u8 k);
extern int func_02055d0c(void *src, void *dst, u32 n);

typedef struct {
    u32 data[12];
} Buf;

void func_0205e8f8(Buf *out, const u8 *key, u32 arg2)
{
    Buf buf;
    u8 k;
    int i;
    k = *key;
    if (*(u16 *) func_0205f100(data_021ca16c, k) != 0xfff1) {
        func_02055d0c(func_0205f130(data_021ca16c, k), &buf, arg2);
    } else {
        for (i = 0; i < 12; i++) {
            buf.data[i] = 0;
        }
    }
    *out = buf;
}
