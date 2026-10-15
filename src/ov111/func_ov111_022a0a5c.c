/* func_ov111_022a0a5c @ 0x022a0a5c, 0xc4 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

// Twelve cases share one body; case 4 is the odd one out.

typedef struct UnkStruct_022a0a5c {
    char pad_00[0x8d];
    u8 unk_8D;
} UnkStruct_022a0a5c;

extern u16 data_021fbe40[];

extern void func_0206f58c(void);
extern int func_0206f56c(void);
extern int func_ov111_022a09f8(UnkStruct_022a0a5c *, int, int);
extern int func_0206fe60(void);
extern int func_ov090_022990e0(void);

int func_ov111_022a0a5c(UnkStruct_022a0a5c *o)
{
    int r;
    u16 w;

    func_0206f58c();
    if (func_0206f56c()) {
        switch (o->unk_8D) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
                return func_ov111_022a09f8(o, 7, 1);
            case 4:
                break;
        }
    }
    if (o->unk_8D != 0 && o->unk_8D != 3 && o->unk_8D != 9) {
        return 0;
    }
    r = -1;
    if (func_0206fe60()) {
        r = func_ov090_022990e0();
    } else {
        w = data_021fbe40[1];
        if (w & 4) {
            r = 7;
        } else if (w & 0x800) {
            r = 0;
        } else if (w & 0x400) {
            r = 5;
        }
    }
    return func_ov111_022a09f8(o, r, 0);
}
