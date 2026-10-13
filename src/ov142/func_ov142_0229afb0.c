/* func_ov142_0229afb0 @ 0x0229afb0, 0x9c bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov002_0220a72c(void *p, int k);
extern int func_ov002_0220a4d4(void *p);

struct UnkStruct_0229afb0 {
    u8 pad_00[0xa0];
    u32 unk_A0;
    u8 pad_A4[0x1c];
    u8 unk_C0;
};

int func_ov142_0229afb0(struct UnkStruct_0229afb0 *s)
{
    u8 b;
    int idx;

    b = s->unk_C0;
    if (b <= 8) {
        return (int) (b << 4) + 31;
    }
    if (b >= 9 && b <= 17) {
        return (((int) (b - 9) << 4) + 0x28) - (int) (s->unk_A0 & 0xf);
    }

    idx = (int) b - 18;

    switch (idx) {
        case 1:
            return func_ov002_0220a72c((char *) s + 0x194, 6);
        case 0:
            return 0x57;
        case 2:
            return func_ov002_0220a4d4((char *) s + 0x14c);
        case 5:
            return func_ov002_0220a72c((char *) s + 0x194, 3);
        case 6:
            return func_ov002_0220a72c((char *) s + 0x194, 4);
        case 3:
            return 0x23;
        case 4:
            return 0x9b;
    }

    return 0x60;
}
