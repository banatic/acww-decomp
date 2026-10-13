/* func_ov068_02270d54 @ 0x02270d54, 0xa4 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02270d54 {
    u8 pad_00[0x204];
    u32 unk_204;
    u8 pad_208[4];
    u32 unk_20C;
    u32 unk_210;
    u32 unk_214;
    u8 pad_218[0x35];
    u8 unk_24D;
};

extern int func_020e8bb0(void *addr, u32 a, u32 b, u32 c, u32 d);
extern void func_02035624(int);
extern void func_020356c4(int, int, int, int);
extern void func_02095ea4(int, int);

void func_ov068_02270d54(struct UnkStruct_02270d54 *p)
{
    char *r = (char *) p + 0x204;
    u32 *q = (u32 *) ((char *) p + 0x210);
    u32 tmp = q[0];
    int flag = 0;

    if (func_020e8bb0(&tmp, 0x1000, 0x200, 0x1000, 0x19a) == 0) {
        flag = 1;
    }

    q[0] = tmp;
    q[1] = tmp;
    q[2] = tmp;

    if (func_020e8bb0(r + 4, 0x2800, 0x199, 0x1000, 0x400) == 0 && flag) {
        *((u8 *) p + 0x251) = 0;
        q[0] = 0x1000;
        q[1] = 0x1000;
        q[2] = 0x1000;
        func_02035624(0x19);
        func_020356c4(0x1a, 0x3f, 0x7f, 0);
        func_02095ea4(0x1a, 4);
    }
}
