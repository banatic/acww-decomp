/* func_ov004_0223ca9c @ 0x0223ca9c, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Slot {
    u8 pad_00[0x40];
};

extern int func_ov004_0223ce84(void);
extern int func_ov004_0223cd78(int a, int b);
extern int func_ov004_0223cb5c(struct Slot *s);

struct Slot *func_ov004_0223ca9c(struct Slot *self, int arg)
{
    int id;
    u32 i;

    id = func_ov004_0223cd78(func_ov004_0223ce84(), arg);
    if (id != -1) {
        for (i = 0; i < 2; i++) {
            if (id == func_ov004_0223cb5c(&self[i])) {
                return &self[i];
            }
        }
    }
    return 0;
}
