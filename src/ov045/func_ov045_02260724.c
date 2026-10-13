/* func_ov045_02260724 @ 0x02260724, 0x88 bytes, Thumb, module ov045
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02260724 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb4 - 0x44];
    char *unk_B4;
} UnkStruct_02260724;

typedef struct Blk {
    int w[10];
} Blk;

extern int func_0206fc6c(void);
extern int func_0206fc44(void);
extern void func_ov045_0226050c(Blk *p);
extern void func_ov045_022604b4(Blk *p);
extern void func_020a8874(Blk *p, int a, int b);
extern void func_020a8a70(Blk *p, Blk *q, int a, int b);
extern void func_02068404(int h, int a, Blk *p);
extern void func_ov045_0226049c(Blk *p);
extern void func_ov045_022604f4(Blk *p);
extern void func_0206844c(int h, u8 *p, int k);
extern int data_ov045_02261380;

void func_ov045_02260724(UnkStruct_02260724 *self)
{
    u8 code;
    Blk a;
    Blk b;
    int h;

    h = self->unk_40;
    code = 0xb;
    if (func_0206fc6c() != 0) {
        *(int *) (self->unk_B4 + 0x754) = func_0206fc44();
        func_ov045_0226050c(&a);
        func_ov045_022604b4(&b);
        func_020a8874(&b, *(int *) (self->unk_B4 + 0x754), 0xa);
        func_020a8a70(&a, &b, 0, 0);
        func_02068404(self->unk_40, 0, &a);
        code = 0xa;
        func_ov045_0226049c(&b);
        func_ov045_022604f4(&a);
    }
    func_0206844c(h, &code, data_ov045_02261380);
}
