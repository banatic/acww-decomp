/* func_020e9548 @ 0x020e9548, 0xb0 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u8 data_021fbe38;
extern u16 data_021fbe3c;
extern struct {
    u16 x;
    u16 y;
    u16 z;
} data_021fbe40;
extern s16 data_02138f6c[];

#define REG_UNKNOWN (*(volatile u16 *) 0x027fffa8)
#define REG_KEYINPUT (*(volatile u16 *) 0x04000130)

void func_020e9548(void)
{
    int keys;
    u16 old;
    u32 idx;
    s16 tab;
    u16 changed;

    if ((REG_UNKNOWN & 0x8000) >> 15) {
        keys = 0;
    } else {
        keys = (u16) (((REG_KEYINPUT | REG_UNKNOWN) ^ 0x2fff) & 0x2fff);
    }

    idx = ((u32) keys & 0xf0) >> 4;
    old = data_021fbe3c;
    tab = data_02138f6c[idx];
    changed = (u16) (keys & (keys ^ old));

    data_021fbe38 = 0;
    data_021fbe40.y = changed;
    data_021fbe3c = (u16) keys;
    data_021fbe40.x = (u16) keys;
    data_021fbe40.z = tab;
}
