/* func_ov077_02278fcc @ 0x02278fcc, 0x9c bytes, Thumb, module ov077
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x8e];
    u16 unk_8E;
    u8 pad_90[0x94 - 0x90];
    u16 unk_94;
    u8 pad_96[0x190 - 0x96];
    u32 unk_190;
    u8 pad_194[0x724 - 0x194];
    u32 unk_724;
} UnkStruct_02278fcc;

extern int func_02096190(int);
extern u16 func_0201c314(void *a, int b);
extern int func_02016884(void *a, int b, void *c);
extern int func_02019de8(void *a);
extern void func_0209129c(int);
extern void func_ov077_02279358(void *a, int b);

int func_ov077_02278fcc(void *self)
{
    UnkStruct_02278fcc *p = (UnkStruct_02278fcc *) self;
    u16 v;
    u32 w;
    signed short val;

    v = func_0201c314(self, func_02096190(4));
    p->unk_8E = v;
    p->unk_94 = v;

    w = p->unk_190;
    val = (signed short) ((w << 4) >> 16);
    if (val == 12) {
        func_0209129c(p->unk_724);
        p->unk_724 = -1;
    }

    if (func_02016884((char *) self + 0x334, 0xfd, (char *) self + 0x2a0) != 0 && func_02019de8((char *) self + 0x564) != 0) {
        if (p->unk_724 != -1) {
            func_0209129c(p->unk_724);
            p->unk_724 = -1;
        }
        func_ov077_02279358(self, 1);
        return 1;
    }
    return 1;
}
