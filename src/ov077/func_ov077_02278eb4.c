/* func_ov077_02278eb4 @ 0x02278eb4, 0xd0 bytes, Thumb, module ov077
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x8e];
    volatile u16 unk_8E;
    char pad_90[0x94 - 0x90];
    volatile u16 unk_94;
    char pad_96[0x190 - 0x96];
    unsigned int unk_190;
    char pad_194[0x724 - 0x194];
    int unk_724;
} UnkStruct_02278eb4;

extern int func_02096190(int a);
extern u16 func_0201c314(UnkStruct_02278eb4 *self, int a);
extern int func_020912d4(int a, void *p, int b, int c);
extern void func_0209129c(int h);
extern int func_02016884(void *a, int b, void *c);
extern int func_02019de8(void *a);
extern void *func_0203e020(UnkStruct_02278eb4 *self);
extern void *func_0208602c(void *p);
extern void *func_020860c8(void *p);
extern void func_02087e9c(void *p, int a);
extern void func_020ee470(UnkStruct_02278eb4 *self);

int func_ov077_02278eb4(UnkStruct_02278eb4 *self)
{
    u16 r;
    unsigned int v;
    short k;

    r = func_0201c314(self, func_02096190(4));
    self->unk_8E = r;
    self->unk_94 = r;
    v = self->unk_190;
    k = (short) ((v << 4) >> 16);
    if (k == 2) {
        self->unk_724 = func_020912d4(0x30, (char *) self + 0x5c, 0, 0);
    }
    if (k == 0xc) {
        if (self->unk_724 != -1) {
            func_0209129c(self->unk_724);
            self->unk_724 = -1;
        }
    }
    if (func_02016884((char *) self + 0x334, 0xfe, (char *) self + 0x2a0) != 0 && func_02019de8((char *) self + 0x564) != 0) {
        func_02087e9c(func_020860c8(func_0208602c(func_0203e020(self))), 0);
        func_020ee470(self);
        if (self->unk_724 != -1) {
            func_0209129c(self->unk_724);
            self->unk_724 = -1;
        }
        return 1;
    }
    return 1;
}
