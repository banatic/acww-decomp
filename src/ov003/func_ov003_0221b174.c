/* func_ov003_0221b174 @ 0x0221b174, 0x120 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_propagation off

struct UnkStruct_0221b174 {
    char pad_00[8];
    int unk_08;
    char pad_0C[0x5c - 0xc];
    int unk_5C;
    int unk_60;
    int unk_64;
    char pad_68[0x26c - 0x68];
    int unk_26C;
    char pad_270[0x328 - 0x270];
    char unk_328[1];
    char pad_329[0x378 - 0x329];
    u16 field_378 : 2;
    u16 field_378_pad : 14;
    char pad_37A[0x39a - 0x37a];
    char unk_39A[1];
    char pad_39B[0x39c - 0x39b];
    int unk_39C;
    int unk_3A0;
};
extern void *data_021c80bc;
extern void func_0204f818(int *out1, int *out2, void *p);
extern int func_0204f5e0(void *p, int h1, int h2, int l1, int l2, int zero);
extern int func_0204bb54(void);
extern void func_0204f538(void *p, u16 *s, int out1, int out2, int zero);
extern int func_ov003_0221a608(int a, void *b, void *c);
extern int func_ov003_0221a538(int a, void *b, void *c);
extern void func_020b0540(void *a, int b);
extern void func_ov003_0221a484(void *a);
extern char *func_020b03f8(void);
extern void func_020044a0(void *a);
extern void func_ov003_02236230(void *self);
extern unsigned char data_021f3b56[];

void func_ov003_0221b174(struct UnkStruct_0221b174 *self)
{
    unsigned int val;
    if (self->unk_39C == 9) {
        void *p = data_021c80bc;
        volatile int out1;
        volatile int out2;
        u16 s;
        int o1;
        int o2;
        int lx;
        int ly;
        int high1;
        int high2;
        int low2;
        int low1;
        func_0204f818((int *) (&out1), (int *) (&out2), ((char *) self) + 0x5c);
        o1 = out1;
        o2 = out2;
        lx = o1;
        ly = o2;
        high1 = lx >> 4;
        high2 = ly >> 4;

        if (func_0204f5e0(p, high1, high2, o1 - (high1 << 4), o2 - (high2 << 4), 0) != 0) {
            if (func_0204bb54() != 0) {
                s = 0xfff1;
                func_0204f538(p, &s, out1, out2, 0);
            }
        }
        if (func_ov003_0221a608(self->field_378, ((char *) self) + 0x5c, ((char *) self) + 0x39a) == 0) {
            if (func_ov003_0221a538(self->field_378, ((char *) self) + 0x5c, ((char *) self) + 0x39a) == 0) {
                func_020b0540((void *) data_021f3b56, self->field_378);
            }
        }
        func_ov003_0221a484(((char *) self) + 0x39a);
    }
    if ((self->unk_3A0 == 0) && (self->unk_39C == 0)) {
        int r4 = self->unk_08 & 1;
        char *base = func_020b03f8();
        r4 = (r4 & 1) << 4;
        *((int *) (base + r4)) = self->unk_5C;
        val = self->unk_60;
        base += r4;
        *((int *) (base + 4)) = val;
        *((int *) (base + 8)) = self->unk_64;
        {
            int r6 = self->unk_26C;
            int r4_2 = self->unk_08 & 1;
            char *base2 = func_020b03f8();
            int off2 = (r4_2 & 1) << 4;
            *((int *) ((base2 + off2) + 12)) = r6;
        }
    }
    func_020044a0(((char *) self) + 0x328);
    func_ov003_02236230(self);
}
