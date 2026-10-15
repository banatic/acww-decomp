/* func_ov004_0221626c @ 0x0221626c, 0xe4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0221626c {
    int d[10];
};

extern void func_0203ee14(void *self, void *p);
extern void func_020a8164(void *p, void *d);
extern void *data_ov004_022531f0;
extern int func_020b6680(void);
extern int func_020b66b0(void);
extern int func_0207cec0(void *d, int a);
extern unsigned int func_0207f2c4(int result);
extern void *func_02062f90(struct UnkStruct_0221626c *o, u16 *p);
extern void func_020683b4(void *h, int a, struct UnkStruct_0221626c *o, int k);
extern void *func_02062f4c(struct UnkStruct_0221626c *o);
extern u16 *func_02060b70(void);
extern int data_021e5a2c;

typedef struct UnkStruct_0221626c_2 {
    char pad_00[8];
    unsigned int unk_08;
} UnkStruct_0221626c_2;
typedef struct Main {
    char pad_00[0xec];
    char sub[0x1e];
    u8 unk_10A;
    char pad_10B[0x21];
    UnkStruct_0221626c_2 *unk_12C;
} Main;

int func_ov004_0221626c(Main *self)
{
    u16 tv[4];
    struct UnkStruct_0221626c a;
    struct UnkStruct_0221626c b;
    void *p;
    unsigned int n;
    int m;
    u16 v;
    u16 *q;

    p = self;
    if (self != 0) {
        p = (char *) self + 0xec;
    }
    func_0203ee14(self, p);
    self->unk_12C->unk_08 = 1;
    func_020a8164((char *) self + 0xec, &data_ov004_022531f0);
    if (func_020b6680() != 0) {
        n = 0;
        if ((m = func_0207cec0(&data_021e5a2c, func_020b66b0())) != 0) {
            n = func_0207f2c4(m);
        }
        tv[2] = (n < 0x46) ? (u16) (n + 0x1323) : (u16) 0x1323;
        func_02062f90(&a, &tv[2]);
        self->unk_10A = 5;
        func_020683b4(self->unk_12C, 0, &a, 7);
        func_02062f4c(&a);
    } else {
        q = func_02060b70();
        m = 0;
        v = *q;
        if (v >= 0x1323 && v <= 0x1368) {
            m = 1;
        }
        if (m != 0) {
            func_02062f90(&b, q);
            self->unk_10A = 5;
            func_020683b4(self->unk_12C, 0, &b, 7);
            func_02062f4c(&b);
        } else {
            self->unk_10A = 6;
        }
    }
    return 1;
}
