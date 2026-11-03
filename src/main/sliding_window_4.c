/* sliding_window_4: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208aecc @ 0x0208aecc, 0x20 bytes, Thumb
 * func_0208aeb8 @ 0x0208aeb8, 0x14 bytes, Thumb
 * func_0208ae98 @ 0x0208ae98, 0x20 bytes, Thumb
 * func_0208ae94 @ 0x0208ae94, 0x4 bytes, Thumb
 * func_0208ae90 @ 0x0208ae90, 0x4 bytes, Thumb
 * func_0208ade8 @ 0x0208ade8, 0xa8 bytes, Thumb
 * func_0208ada8 @ 0x0208ada8, 0x40 bytes, Thumb
 * func_0208ad64 @ 0x0208ad64, 0x44 bytes, Thumb
 * func_0208ad24 @ 0x0208ad24, 0x40 bytes, Thumb
 * func_0208ab3c @ 0x0208ab3c, 0x1e8 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0208aecc {
    volatile void *unk_00;
};

typedef struct UnkStruct_0208ade8 {
    void *unk_00;
    u8 pad_04[8];
    u8 sub1[0x14];
    u8 sub2[0x14];
    int unk_34;
    int unk_38;
    int unk_3C;
    int unk_40;
    int unk_44;
    int unk_48;
    int unk_4C;
    int unk_50;
    u8 bytes[9];
    u8 pad_5D[3];
    u8 sub3[0x30];
    u8 sub4[0x30];
    int c0;
    int c4;
    int c8;
} UnkStruct_0208ade8;

struct UnkStruct_0208ad24 {
    void *unk_00;
};

typedef struct {
    unsigned char pad_00[0x34];
    int unk_34;
    unsigned char pad_38[0x44 - 0x38];
    int unk_44;
    unsigned char pad_48[0x56 - 0x48];
    unsigned char unk_56;
    unsigned char pad_57;
    unsigned char unk_58;
    unsigned char pad_59[0x5b - 0x59];
    unsigned char unk_5B;
} UnkStruct_0208ab3c;

extern void func_02051ad8(void *obj);
extern unsigned char data_020da6dc[];
extern unsigned char data_020e2094[];
extern void func_020edb3c(void *p);
extern void func_0208af30(void *self);
extern void func_0208a1f8(void *sub);
extern void func_0208a738(void *self);
extern void func_0208a9a4(void *self);
extern void func_0208a4dc(void *p);
extern void func_0208a1f4(void *p);
extern void func_0208af00(void *p);
extern unsigned char data_020e20ac[];
extern int func_0208a1d0(void *p);
extern int func_0208a824(void *p);
extern int func_0208a80c(void *p);
extern int func_0208a1b0(void *p, int v);
extern int func_0208a198(void *p, int v);
extern void func_02088df8(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11, int a12);

void *func_0208aecc(void *self)
{
    struct UnkStruct_0208aecc *obj = (struct UnkStruct_0208aecc *) self;
    obj->unk_00 = (void *) data_020da6dc;
    obj->unk_00 = (void *) data_020e2094;
    func_02051ad8(self);
    return self;
}

void func_0208aeb8(volatile unsigned int *p)
{
    *p = (unsigned int) (unsigned int) data_020e2094;
    *p = (unsigned int) (unsigned int) data_020da6dc;
}

void *func_0208ae98(volatile unsigned int *p)
{
    *p = (unsigned int) (unsigned int) data_020e2094;
    *p = (unsigned int) (unsigned int) data_020da6dc;
    func_020edb3c((void *) p);
    return (void *) p;
}

int func_0208ae94(void)
{
    return 42;
}

int func_0208ae90(int p0)
{
    return ((int) (p0) + (4));
}

UnkStruct_0208ade8 *func_0208ade8(UnkStruct_0208ade8 *self, int param)
{
    func_0208af30(self);
    self->unk_00 = ((int *) data_020e20ac);
    func_0208a1f8(self->sub1);
    func_0208a1f8(self->sub2);
    self->unk_34 = 0;
    self->unk_38 = 0;
    self->unk_3C = 0;
    self->unk_40 = 0;
    self->unk_44 = -1;
    self->unk_48 = 0;
    self->unk_4C = 0;
    self->unk_50 = 0;
    self->bytes[0] = 0;
    self->bytes[1] = 0;
    self->bytes[2] = param;
    self->bytes[3] = 0;
    self->bytes[4] = 0;
    self->bytes[5] = 0;
    self->bytes[6] = 0;
    self->bytes[7] = 0;
    self->bytes[8] = 0;
    func_0208aecc(self->sub3);
    func_0208aecc(self->sub4);
    self->c0 = 0;
    self->c4 = 0;
    self->c8 = 0;
    func_0208a738(self);
    func_0208a9a4(self);
    return self;
}

void *func_0208ada8(void *p)
{
    *(void **) p = (void *) data_020e20ac;
    func_0208a4dc(p);
    func_0208aeb8((volatile unsigned int *) ((void *) ((char *) p + 0x90)));
    func_0208aeb8((volatile unsigned int *) ((void *) ((char *) p + 0x60)));
    func_0208a1f4((void *) ((char *) p + 0x20));
    func_0208a1f4((void *) ((char *) p + 0x0c));
    func_0208af00(p);
    return p;
}

void *func_0208ad64(void *self)
{
    ((void **) self)[0] = (void *) ((int *) data_020e20ac);
    func_0208a4dc(self);
    func_0208aeb8((volatile unsigned int *) ((char *) self + 0x90));
    func_0208aeb8((volatile unsigned int *) ((char *) self + 0x60));
    func_0208a1f4((char *) self + 0x20);
    func_0208a1f4((char *) self + 0x0c);
    func_0208af00(self);
    func_020edb3c(self);
    return self;
}

struct UnkStruct_0208ad24 *func_0208ad24(struct UnkStruct_0208ad24 *self)
{
    self->unk_00 = ((char *) data_020e20ac);
    func_0208a4dc(self);
    func_0208aeb8((volatile unsigned int *) ((char *) self + 0x90));
    func_0208aeb8((volatile unsigned int *) ((char *) self + 0x60));
    func_0208a1f4((char *) self + 0x20);
    func_0208a1f4((char *) self + 0xc);
    func_0208af00(self);
    return self;
}

void func_0208ab3c(UnkStruct_0208ab3c *p)
{
    int a1, a2, b, c;
    int r4, r6, r7, v28;

    if (p->unk_34 == 0) {
        return;
    }

    a1 = func_0208a1d0((char *) p + 0xc);
    a2 = func_0208a1d0((char *) p + 0x20);
    b = func_0208a824(p);
    c = func_0208a80c(p);

    r4 = b + func_0208a1b0((char *) p + 0xc, -1);
    r7 = c + func_0208a198((char *) p + 0xc, -1);
    r6 = b + func_0208a1b0((char *) p + 0x20, -1);
    v28 = c + func_0208a198((char *) p + 0x20, -1);

    if (p->unk_56 != 0) {
        func_02088df8(0, a1, r4, r7, -1, p->unk_44, 0x1000, 0x1000, 0, -1, 0, 0);
        if (p->unk_5B != 0) {
            func_02088df8(0, a2, r6, v28, -1, p->unk_44, 0x1000, 0x1000, 0, -1, 0, 0);
        }
        if (p->unk_58 != 0) {
            func_02088df8(0, a1, r4, r7, -1, p->unk_44, 0x1000, 0x1000, 0, 2, 0, 0);
            if (p->unk_5B != 0) {
                func_02088df8(0, a2, r6, v28, -1, p->unk_44, 0x1000, 0x1000, 0, 2, 0, 0);
            }
        }
    } else {
        func_02088df8(1, a1, r4, r7, -1, p->unk_44, 0x1000, 0x1000, 0, -1, 0, 0);
        if (p->unk_5B != 0) {
            func_02088df8(1, a2, r6, v28, -1, p->unk_44, 0x1000, 0x1000, 0, -1, 0, 0);
        }
        if (p->unk_58 != 0) {
            func_02088df8(1, a1, r4, r7, -1, p->unk_44, 0x1000, 0x1000, 0, 2, 0, 0);
            if (p->unk_5B != 0) {
                func_02088df8(1, a2, r6, v28, -1, p->unk_44, 0x1000, 0x1000, 0, 2, 0, 0);
            }
        }
    }
}
