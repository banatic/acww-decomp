/* func_ov142_0229b04c @ 0x0229b04c, 0x88 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0229b04c {
    char pad_00[0xc0];
    u8 unk_C0;
} UnkStruct_0229b04c;

extern int func_ov002_0220a768(void *, int);
extern int func_ov002_0220a4f8(void *);

int func_ov142_0229b04c(UnkStruct_0229b04c *o)
{
    u8 v = o->unk_C0;

    if (v <= 8) {
        return 0x17;
    }
    if (v >= 9 && v <= 0x11) {
        return 0x40;
    }
    switch (v) {
        case 0x13:
            return func_ov002_0220a768((char *) o + 0x194, 6);
        case 0x12:
            return 0xe8;
        case 0x14:
            return func_ov002_0220a4f8((char *) o + 0x14c);
        case 0x17:
            return func_ov002_0220a768((char *) o + 0x194, 3);
        case 0x18:
            return func_ov002_0220a768((char *) o + 0x194, 4);
        case 0x15:
        case 0x16:
            return 0xc0;
    }
    return 0x80;
}
