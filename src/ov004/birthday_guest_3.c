/* birthday_guest_3: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0221e2cc @ 0x0221e2cc, 0x3c bytes, Thumb
 * func_ov004_0221e2c0 @ 0x0221e2c0, 0xc bytes, Thumb
 * func_ov004_0221e1e0 @ 0x0221e1e0, 0xe0 bytes, Thumb
 * func_ov004_0221e1a0 @ 0x0221e1a0, 0x40 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0221e1a0 {
    u8 pad_00[0x89c];
    u8 sub[4];
};

extern void *func_020edf70(int);
extern void *func_0202e8e4(void *);
extern void *func_0202decc(void *);
extern int data_ov004_02253868;
extern int data_ov004_022537d8;
extern unsigned int data_ov004_02257bc4;
extern void func_0204f818(int *out0, int *out1, const int *in);
extern int func_02031a08(int i, int j);
extern int func_020644cc(int n);
extern void func_0204f794(int *out, int i, int j);
extern int func_020e8ed8(int dx, int dy);
extern int func_020e8b4c(int a, int b);
extern int func_0202e364(struct UnkStruct_0221e1a0 *self);
extern void func_0201c280(struct UnkStruct_0221e1a0 *self, void *p);
extern void func_ov004_0221defc(void *p, struct UnkStruct_0221e1a0 *self);
extern int func_ov004_0221dd24(struct UnkStruct_0221e1a0 *self, int a);

void *func_ov004_0221e2cc(void)
{
    u8 *p;
    p = (u8 *) func_020edf70(0xa6c);
    if (p != 0) {
        func_0202e8e4(p);
        *(int **) p = &data_ov004_02253868;
        func_0202decc(p + 0x89c);
        *(int **) (p + 0x89c) = &data_ov004_022537d8;
    }
    return p;
}

unsigned int func_ov004_0221e2c0(void)
{
    return data_ov004_02257bc4;
}

int func_ov004_0221e1e0(int *out, int *in, int a)
{
    // DECLS
    int ang;
    int count;
    int gx;
    int j;
    int i;
    int gz;
    int target;
    int k;
    // ENDDECLS

    func_0204f818(&gx, &gz, in);
    count = 0;
    for (j = 0; j < 0xe; j++) {
        for (i = 0; i < 0x10; i++) {
            if (i != gx && j != gz && func_02031a08(i, j) != 0) {
                count++;
            }
        }
    }
    out[0] = in[0];
    out[1] = in[1];
    out[2] = in[2];
    if (count != 0) {
        target = func_020644cc(count);
        k = 0;
        for (j = 0; j < 0xe; j++) {
            for (i = 0; i < 0x10; i++) {
                if (i != gx && j != gz && func_02031a08(i, j) != 0) {
                    if (k == target) {
                        func_0204f794(out, i, j);
                        ang = func_020e8ed8(out[0] - in[0], out[2] - in[2]);
                        if (func_020e8b4c(a, ang) < 0x2000) {
                            ang = a;
                        }
                        return ang;
                    }
                    k = k + 1;
                }
            }
        }
    }
    return a;
}

int func_ov004_0221e1a0(struct UnkStruct_0221e1a0 *self)
{
    if (!func_0202e364(self)) {
        return 0;
    }
    (*(struct UnkStruct_0221e1a0 * *) &data_ov004_02257bc4) = self;
    func_0201c280(self, &self->sub);
    func_ov004_0221defc(&self->sub, self);
    func_ov004_0221dd24(self, 0);
    return 1;
}
