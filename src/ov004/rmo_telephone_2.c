/* rmo_telephone_2: 12 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02230f64 @ 0x02230f64, 0x10 bytes, Thumb
 * func_ov004_02230f38 @ 0x02230f38, 0x2c bytes, Thumb
 * func_ov004_02230f18 @ 0x02230f18, 0x20 bytes, Thumb
 * func_ov004_02230ef4 @ 0x02230ef4, 0x24 bytes, Thumb
 * func_ov004_02230ef0 @ 0x02230ef0, 0x2 bytes, Thumb
 * func_ov004_02230ec4 @ 0x02230ec4, 0x2c bytes, Thumb
 * func_ov004_02230ec0 @ 0x02230ec0, 0x2 bytes, Thumb
 * func_ov004_02230e94 @ 0x02230e94, 0x2c bytes, Thumb
 * func_ov004_02230e90 @ 0x02230e90, 0x2 bytes, Thumb
 * func_ov004_02230e6c @ 0x02230e6c, 0x24 bytes, Thumb
 * func_ov004_02230e68 @ 0x02230e68, 0x2 bytes, Thumb
 * func_ov004_02230e08 @ 0x02230e08, 0x60 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02230ef4;

struct UnkStruct_02230ef4_2;

struct UnkStruct_02230ef4 {
    int pad_00;
    void *unk_04;
};

struct UnkStruct_02230ef4_2 {
    char pad_00[720];
    struct UnkStruct_02230ef4 *b;
};

extern char data_ov004_022558ac[];
extern void func_ov004_02230db8(char *self, void *p1, unsigned char p2);
extern void *func_020682e0(int k);
extern void func_02068320(void *p);
extern void func_ov004_0223121c(void *self, int k);
extern int func_0206fbf8(int a);
extern int func_0206fbc0(void);
extern int func_0206fc6c(void);
extern void func_0206844c(void *, u8 *, void *);
extern int func_020b65c4(void);

void func_ov004_02230f64(int a)
{
    func_ov004_02230db8((char *) a, data_ov004_022558ac, 0x22);
    return;
}

void func_ov004_02230f38(void *self)
{
    void *p = func_020682e0(0);
    if (*(void **) ((char *) p + 4) == 0) {
        func_02068320(p);
        *((char *) self + 0x63c) = 0;
        func_ov004_0223121c(self, 7);
    }
}

int func_ov004_02230f18(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_02230db8((char *) self, ((void **) data_ov004_022558ac), 0xe);
    *(u8 *) (self + 0x63c) = 0x1;
    return 0x63c;
}

void func_ov004_02230ef4(struct UnkStruct_02230ef4_2 *self)
{
    struct UnkStruct_02230ef4 *b;
    b = self->b;
    if (b != 0) {
        if (b->unk_04 != 0) {
            func_ov004_0223121c((void *) self, 11);
        }
    }
}

void func_ov004_02230ef0(void) {}

void func_ov004_02230ec4(void *self)
{
    void *p = func_020682e0(0);
    if (*(void **) ((char *) p + 4) == 0) {
        func_02068320(p);
        *((char *) self + 0x63c) = 0;
        func_ov004_0223121c(self, 7);
    }
}

void func_ov004_02230ec0(void) {}

void func_ov004_02230e94(void *self)
{
    void *p = func_020682e0(0);
    if (*(void **) ((char *) p + 4) == 0) {
        func_02068320(p);
        *((char *) self + 0x63c) = 0;
        func_ov004_0223121c(self, 7);
    }
}

void func_ov004_02230e90(void) {}

void func_ov004_02230e6c(char *self)
{
    if (*(int *) ((char *) func_020682e0(0) + 4) == 5) {
        func_0206fbf8(0x30);
        func_ov004_0223121c((void *) self, 0xe);
    }
}

void func_ov004_02230e68(void) {}

void func_ov004_02230e08(void *self)
{
    u8 b;
    if (func_0206fbc0() != 0) {
        void *h = func_020682e0(0);
        b = 0x10;
        if (func_0206fc6c() == 0) {
            b = 0x18;
        }
        func_0206844c(h, &b, ((int *) data_ov004_022558ac));
        *(int *) ((char *) h + 8) = 1;
        if (func_020b65c4() == 6) {
            func_ov004_0223121c(self, 0xc);
        } else {
            func_ov004_0223121c(self, 4);
        }
    }
}
