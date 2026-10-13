/* func_020215f4 @ 0x020215f4, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void MI_CpuCopy8(const void *src, void *dest, u32 size);
extern int func_0203fc78(void *entry, void *buf, int prev);
extern void *data_020c8fe0[12];
extern int data_020c8a48;

void *func_020215f4(int unused, u8 *flagOut, int *valOut, u8 *kindOut, const void *src)
{
    u8 buf[8];
    int idx;
    int i;
    int result;

    result = 0;
    idx = -1;
    for (i = 0; i < 12; i++) {
        MI_CpuCopy8(src, buf, 8);
        {
            unsigned int hit = func_0203fc78(data_020c8fe0[i], buf, result) ? 1 : result;
            if (hit > 0) {
                idx = i;
                break;
            }
        }
    }
    if ((u32) idx < 12) {
        if (idx % 3 == 2) {
            *valOut = (idx / 3 + 1) * 5 - 1;
            *kindOut = 1;
        } else {
            *valOut = idx * 2 - idx / 3;
            *kindOut = 2;
        }
        *flagOut = 1;
        result = data_020c8a48;
    }
    return (void *) result;
}
