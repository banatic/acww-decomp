/* func_ov146_02299a4c @ 0x02299a4c, 0xa8 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

typedef struct UnkStruct_02299a4c {
    u8 pad_00[0xae];
    s16 unk_AE;
    u8 unk_B0;
    u8 pad_B1[0xbb - 0xb0 - 1];
    u8 unk_BB;
    u8 pad_BC[0xea - 0xbb - 1];
    u8 arr_ea[0x20];
} UnkStruct_02299a4c;

extern int func_ov146_02299e9c(UnkStruct_02299a4c *self, u8 v);
extern void func_0200467c(int a);
extern void func_ov146_02299660(UnkStruct_02299a4c *self, int a);
extern void func_ov002_0220a574(void *p);
extern void func_ov002_0220a4bc(void *receiver);
extern unsigned char *func_ov002_02208098(UnkStruct_02299a4c *self, unsigned char value);
extern void func_ov146_0229a6dc(UnkStruct_02299a4c *self);
extern void func_ov146_0229a6a4(UnkStruct_02299a4c *self);

int func_ov146_02299a4c(UnkStruct_02299a4c *self, unsigned int p)
{
    if (p >= 3 && p <= 9) {
        int i = self->unk_AE + p - 3;
        u8 v;

        if (i >= 0x20) {
            return 0;
        }

        v = self->arr_ea[i];
        if (func_ov146_02299e9c(self, v) != 0) {
            self->unk_BB = v;
            func_0200467c(0x29);
            func_ov146_02299660(self, 0x10);
            func_ov146_02299660(self, 0x20);
        }
        return 0;
    }

    switch (p) {
        case 2:
            func_ov002_0220a574((char *) self + 0x1fb4);
            func_ov002_0220a4bc((void *) ((char *) self + 0x1fb4));
            func_ov002_02208098(self, 4);
            return 1;
        case 1:
            if (self->unk_B0 == 8) {
                func_ov146_0229a6dc(self);
                return 1;
            }
            return 0;
        case 0:
            func_ov146_0229a6a4(self);
            return 1;
    }
    return 0;
}
