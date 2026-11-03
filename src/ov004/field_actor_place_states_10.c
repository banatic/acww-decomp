/* field_actor_place_states_10: 7 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222bdec @ 0x0222bdec, 0x4 bytes, Thumb
 * func_ov004_0222bd6c @ 0x0222bd6c, 0x80 bytes, Thumb
 * func_ov004_0222bd40 @ 0x0222bd40, 0x2c bytes, Thumb
 * func_ov004_0222bcf4 @ 0x0222bcf4, 0x4c bytes, Thumb
 * func_ov004_0222bc60 @ 0x0222bc60, 0x94 bytes, Thumb
 * func_ov004_0222bc28 @ 0x0222bc28, 0x38 bytes, Thumb
 * func_ov004_0222bc24 @ 0x0222bc24, 0x4 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char unk_00;
} UnkStruct_0222bdec;

struct some_struct {
    char pad_00[0x800];
    int unk_800;
};

typedef struct {
    unsigned char unk_00;
} UnkStruct_0222bc24;

extern int func_02073908(int a, int b);
extern void func_020109fc(void *self, int a, int b, int c);
extern int func_0203e110(void);
extern int data_020ccf94;
extern int func_ov004_0222bdf0(void *, int, int, int);
extern int func_0200f328(void *, int);
extern int func_02011340(void *);
extern int func_020b67ac(void);
extern int func_0200dc8c(void *self);
extern int func_0200dc2c(void *self);
extern int func_ov004_0223c510(void *p, short a);
extern int func_ov004_0223c4b8(void *p, short a);
extern int func_ov004_0222b6a8(void *self, int a, int b, int c);
extern int func_ov004_0222bbe4(void *self, int a, int b, int c);
extern int func_0200f554(void *);
extern void func_02010f5c(void *);
extern int func_02010ca4(void *);

void func_ov004_0222bdec(UnkStruct_0222bdec *p, unsigned char v)
{
    p->unk_00 = v;
}

void func_ov004_0222bd6c(unsigned char *self, unsigned char *p, int m)
{
    unsigned char *q, *w;
    q = p + 0xc;
    w = self + 0x7d4;
    if (*(int *) (self + 0x704) != 0x11) {
        if (m == 0xf || m == 0xd || func_02073908(data_020ccf94, *(int *) (self + 0x800)) == 0) {
            func_020109fc(self, 0x11, 0, 0);
        } else {
            func_020109fc(self, 0x11, 3, 0);
        }
    }
    func_ov004_0222bdec((UnkStruct_0222bdec *) w, *q);
    if (*w == 0) {
        if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) != 0) {
            func_0203e110();
        }
    }
}

void func_ov004_0222bd40(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    if (*(int *) (self + 0x7f0) == 0x8) {
        *(u16 *) (self + 0xc84) = a1;
    } else {
        func_ov004_0222bdf0(self, 0x0, 0x6, a1);
    }
}

void func_ov004_0222bcf4(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    if (func_020b67ac() != 0x0 && a1 == 0xa && *(u8 *) (self + 0x7d4) == 0x0) {
        if (func_02011340(self) != 0x0) {
            func_0200f328(self, 0x4cd);
        } else {
            func_0200f328(self, 0x4cc);
        }
    }
}

void func_ov004_0222bc60(char *self)
{
    int k;
    int r;
    unsigned char *p;
    int t, n;

    if (func_020b67ac() != 0) {
        return;
    }
    if (func_0200dc8c(self) <= 0) {
        return;
    }
    k = func_0200dc2c(self);
    if (*(unsigned char *) (self + 0x8ea) == k + 1) {
        return;
    }
    *(unsigned char *) (self + 0x8ea) = k + 1;
    switch (k) {
        case 0:
            r = func_ov004_0223c510(self + 0x5c, *(short *) (self + 0x8e));
            break;
        case 1:
            r = func_ov004_0223c4b8(self + 0x5c, *(short *) (self + 0x8e));
            break;
    }
    if (r == 1) {
        func_ov004_0222b6a8(self, (k == 0) ? 1 : 0, 6, -1);
    } else if (r == 2) {
        func_ov004_0222bbe4(self, (k == 0) ? 1 : 0, 6, -1);
    }
}

void func_ov004_0222bc28(struct some_struct *s)
{
    func_0200f554(s);
    func_02010f5c(s);
    func_02010ca4(s);
    if (func_02073908(data_020ccf94, s->unk_800) != 0) {
        func_ov004_0222bc60((char *) s);
    }
}

void func_ov004_0222bc24(UnkStruct_0222bc24 *p, unsigned char v)
{
    p->unk_00 = v;
}
