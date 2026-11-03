/* birthday_villager_4: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0221d290 @ 0x0221d290, 0x40 bytes, Thumb
 * func_ov004_0221d278 @ 0x0221d278, 0x18 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0221d290 {
    int x;
    int y;
};

struct UnkStruct_0221d290_2 {
    u8 pad_00[0x558];
    u8 sub[0xa48 - 0x558];
    struct UnkStruct_0221d290 v;
};

extern int func_0202e1fc(struct UnkStruct_0221d290_2 *self);
extern void func_02013c0c(void *p);
extern struct UnkStruct_0221d290 data_ov004_0225353c;
extern int func_0201b790(void *arg0);

int func_ov004_0221d290(struct UnkStruct_0221d290_2 *self)
{
    if (!func_0202e1fc(self)) {
        return 0;
    }
    self->v = data_ov004_0225353c;
    func_02013c0c(&self->sub);
    return 1;
}

int func_ov004_0221d278(int result)
{
    if (func_0201b790((void *) result) != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
