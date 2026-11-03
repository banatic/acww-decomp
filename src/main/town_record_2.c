/* town_record_2: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204cf10 @ 0x0204cf10, 0x2 bytes, Thumb
 * func_0204cf0c @ 0x0204cf0c, 0x2 bytes, Thumb
 * func_0204ce64 @ 0x0204ce64, 0xa6 bytes, Thumb
 * func_0204cdfc @ 0x0204cdfc, 0x68 bytes, Thumb
 * func_0204cdc8 @ 0x0204cdc8, 0x32 bytes, Thumb
 */

#include "types.h"

typedef struct {
    u8 unk_00;              // 0x00
    u8 unk_01;              // 0x01
    u8 unk_02;              // 0x02
    u8 pad_03;              // 0x03
    u32 unk_04;             // 0x04
    u8 pad_08[0x21 - 0x08]; // 0x08..0x20
    s8 unk_21;              // 0x21
    u8 unk_22;              // 0x22
    u8 pad_23[0x54 - 0x23]; // 0x23..0x53
    u8 unk_54;              // 0x54
    u8 unk_55;              // 0x55
    u8 unk_56;              // 0x56
    u8 unk_57;              // 0x57
    u8 arr[16];             // 0x58..0x67
    u8 unk_68;              // 0x68
    u8 unk_69;              // 0x69
    u8 unk_6A;              // 0x6a
    u8 unk_6B;              // 0x6b
} UnkStruct_0204ce64;

struct Elem {
    unsigned char unk_00, unk_01, unk_02, unk_03;
};

struct UnkStruct_0204cdfc {
    void *unk_00;
    int unk_04;
    unsigned char unk_08;
    unsigned char unk_09;
    unsigned char unk_0A;
    unsigned char unk_0B;
    char pad_0C[0x15];
    signed char unk_21;
    char pad_22[0x32];
    unsigned char unk_54;
    unsigned char unk_55;
    unsigned char unk_56;
    unsigned char unk_57;
    struct Elem arr[4];
};

extern u32 func_020644cc(int value);
extern int func_0209de88(int a, int b, int c);
extern void func_0204cc34(UnkStruct_0204ce64 *a, UnkStruct_0204ce64 *b);
extern void func_0204cc24(UnkStruct_0204ce64 *self);
extern void func_0204cc14(UnkStruct_0204ce64 *self);
extern void func_0204cd20(UnkStruct_0204ce64 *self);
extern void func_0204cc98(UnkStruct_0204ce64 *self);
extern void func_0204cbe0(UnkStruct_0204ce64 *self);
extern void func_020467cc(void);
extern void func_0209df64(void *p);
extern int func_0209dd9c(void *src, void *dst);

void func_0204cf10(void *self) {}

void func_0204cf0c(void *self) {}

void func_0204ce64(UnkStruct_0204ce64 *self)
{
    u8 *p;
    int i;

    func_0209df64((void *) self);
    self->unk_04 = func_020644cc(5);
    func_0209de88(self->unk_02, self->unk_01, self->unk_00);
    func_0204cc34(self, self);
    func_0204cc24(self);
    func_0204cc14(self);
    func_0204cd20(self);
    func_0204cc98(self);
    func_0204cbe0(self);

    p = self->arr;
    for (i = 0; i < 4; i++) {
        p[0] = 1;
        p[1] = 1;
        p[2] = 0;
        p[3] = 0;
        p += 4;
    }

    self->unk_21 = -1;
    self->unk_54 = 1;
    self->unk_55 = 1;
    self->unk_56 = 0;
    self->unk_57 = 0;

    func_020467cc();

    self->unk_6B = 0;
    self->unk_6A = 0xFF;
    self->unk_69 = 0xFF;
    self->unk_68 = 0xFF;
    self->unk_22 = 0;
}

void func_0204cdfc(struct UnkStruct_0204cdfc *p)
{
    unsigned char zero;
    unsigned char one;
    struct Elem *q;
    int i;

    func_0209df64(p);

    p->unk_04 = 0;
    p->unk_08 = 1;
    p->unk_09 = 1;
    p->unk_0A = 0;
    p->unk_0B = 0;

    func_0204cc24((UnkStruct_0204ce64 *) p);
    func_0204cc14((UnkStruct_0204ce64 *) p);
    func_0204cbe0((UnkStruct_0204ce64 *) p);

    zero = 0;
    one = 1;
    q = p->arr;
    for (i = 0; i < 4; i++) {
        q->unk_00 = one;
        q->unk_01 = one;
        q->unk_02 = zero;
        q->unk_03 = zero;
        q++;
    }

    p->unk_21 = -1;
    p->unk_54 = one;
    p->unk_55 = one;
    p->unk_56 = zero;
    p->unk_57 = zero;
}

void func_0204cdc8(void *arg0)
{
    unsigned char buf[4];
    int result;
    unsigned char *p;
    unsigned char *q;

    p = (unsigned char *) arg0;
    func_0209df64(buf);
    result = func_0209dd9c(buf, p);
    if (result == 0) {
        q = buf;
        p[0] = q[0];
        p[1] = q[1];
        p[2] = q[2];
        p[3] = q[3];
    }
}
