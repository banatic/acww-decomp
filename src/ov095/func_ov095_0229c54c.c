/* func_ov095_0229c54c @ 0x0229c54c, 0xb0 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0229c54c {
    char pad_00[0x16];
    u8 unk_16;
    char pad_17[0xd];
    int unk_24;
} UnkStruct_0229c54c;

extern int func_ov095_0229c5fc(UnkStruct_0229c54c *, int, u8);
extern int func_ov095_022999b0(UnkStruct_0229c54c *, int);
extern int func_ov095_0229c7c8(UnkStruct_0229c54c *, int, int);
extern int func_ov095_0229c750(UnkStruct_0229c54c *, int, int);
extern int func_ov095_0229c654(UnkStruct_0229c54c *, int, int);
extern int func_ov095_0229ce08(UnkStruct_0229c54c *, int);

int func_ov095_0229c54c(UnkStruct_0229c54c *o, int a, u8 b)
{
    int r;

    o->unk_24 = -1;
    r = func_ov095_0229c5fc(o, a, b);
    if (r == -1) {
        if (func_ov095_022999b0(o, 4) == 0) {
            if (b < 0xf7) {
                b = b + 8;
            } else {
                b = 0xff;
            }
        }
        switch (o->unk_16) {
            case 0:
                break;
            case 1:
                r = func_ov095_0229c7c8(o, a, b);
                if (r == 0x6a || r == 0x6c || r == 0x6d) {
                    r = 0x6b;
                }
                break;
            case 2:
                r = func_ov095_0229c750(o, a, b);
                break;
            case 3:
                break;
            case 4:
                r = func_ov095_0229c654(o, a, b);
                break;
            default:
                return -1;
        }
    }
    if (func_ov095_0229ce08(o, r) != 0) {
        return -1;
    }
    o->unk_24 = r;
    return r;
}
