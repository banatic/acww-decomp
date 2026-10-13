/* func_020be568 @ 0x020be568, 0x38 bytes, Thumb, module main
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
extern void func_020042b0(struct SomeItem *a, struct SomeItem *b);

void func_020be568(struct SomeObj *obj)
{
    struct SomeItem *a;
    struct SomeItem *b;
    int i;
    if (*(unsigned char *) ((char *) obj + 0xc0) == 0) {
        return;
    }
    a = obj->items;
    b = (struct SomeItem *) ((char *) obj + 0x60);
    for (i = 0; i < 8; i++, a++, b++) {
        func_020042b0(a, i == 7 ? 0 : b);
    }
}
