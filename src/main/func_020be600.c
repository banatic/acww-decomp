/* func_020be600 @ 0x020be600, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct SomeItem {
    u8 data[12];
};

struct SomeObj {
    struct SomeItem items[8];
    u8 pad_60[0x60];
    u8 flag_C0;
};

extern void func_02004280(struct SomeItem *item);

void func_020be600(struct SomeObj *obj)
{
    struct SomeItem *p;

    obj->flag_C0 = 0;
    for (p = &obj->items[7]; p >= obj->items; p--) {
        func_02004280(p);
    }
}
