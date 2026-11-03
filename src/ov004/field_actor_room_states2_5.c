/* field_actor_room_states2_5: 6 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222a3cc @ 0x0222a3cc, 0x38 bytes, Thumb
 * func_ov004_0222a3ac @ 0x0222a3ac, 0x20 bytes, Thumb
 * func_ov004_0222a390 @ 0x0222a390, 0x1c bytes, Thumb
 * func_ov004_0222a2e8 @ 0x0222a2e8, 0xa8 bytes, Thumb
 * func_ov004_0222a28c @ 0x0222a28c, 0x5c bytes, Thumb
 * func_ov004_0222a284 @ 0x0222a284, 0x6 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned int a;
    unsigned int b;
    short c;
} UnkStruct_0222a390;

typedef struct {
    unsigned char pad_00[0x7d4];
    UnkStruct_0222a390 sub;
} UnkStruct_0222a390_2;

typedef struct {
    unsigned char pad_00[0x7f0];
    int unk_7F0;
    unsigned char pad_7F4[0x8];
    int unk_7FC;
    int unk_800;
} Obj_020d82b4;

struct Pair {
    u8 a;
    u8 b;
};

extern void func_ov004_0222a450(void *dst, int *x, int *y, short *z);
extern int func_ov004_0222a494(void *self, int x, int y, short z, int a, int k);
extern void func_020110a0(void *object, short *values);
extern void func_0200fbc4(UnkStruct_0222a390_2 *self, unsigned int a, unsigned int b, short c);
extern int func_02056f94(void *p);
extern int func_ov004_0222a23c(void *self, int a, int b, int arg, short v);
extern int func_ov004_0223cb10(void);
extern void func_ov004_0223c9d4(int h);
extern int func_02008258(void *self, int a);
extern int func_0200d4e8(void *self, int a, int b, int c);
extern int data_020ccf94;
void func_02010f5c(void *self);
int func_0201100c(void *self);
void func_02010d64(void *self);
int func_02010ca4(void *self);
int func_02073908(int a, int b);

void func_ov004_0222a3cc(unsigned char *self, int k)
{
    short z;
    int x, y;
    func_ov004_0222a450(self + 0x8f0, &x, &y, &z);
    func_ov004_0222a494(self, x, y, z, 5, k);
}

void func_ov004_0222a3ac(char *self, int stateId)
{
    const int *src = (const int *) (self + 0x7d4);
    int *dst = (int *) (self + 0x5c);
    dst[0] = src[0];
    dst[2] = src[1];
    func_020110a0(self, (short *) (src + 2));
}

void func_ov004_0222a390(UnkStruct_0222a390_2 *self)
{
    UnkStruct_0222a390 *s;
    s = &self->sub;
    func_0200fbc4(self, s->a, s->b, s->c);
}

void func_ov004_0222a2e8(char *self)
{
    int *q;
    int *v;

    q = (int *) (self + 0x7d4);
    v = (int *) (self + 0x5c);
    if (func_02056f94(self + 0x2d0) != 0 && v[0] == q[0] && v[2] == q[1] &&
        *(short *) ((char *) q + 8) == *(short *) (self + 0x8e)) {
        func_ov004_0222a23c(self, 1, 0, 5, -1);
        return;
    }
    if (*(unsigned char *) (self + 0x141) != 0) {
        return;
    }
    if (*((unsigned char *) q + 0xa) == 0) {
        *((unsigned char *) q + 0xa) = 1;
        if (func_02056f94(self + 0x2d0) == 0) {
            func_ov004_0223c9d4(func_ov004_0223cb10());
        }
    } else {
        *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
        func_0200d4e8(self, 3, 1, -1);
    }
}

void func_ov004_0222a28c(Obj_020d82b4 *self)
{
    func_ov004_0222a390((UnkStruct_0222a390_2 *) self);
    func_02010f5c(self);
    func_0201100c(self);
    func_02010d64(self);
    func_02010ca4(self);

    if (func_02073908(data_020ccf94, self->unk_800) != 0) {
        func_ov004_0222a2e8((char *) self);
    } else {
        self->unk_7FC = func_02008258(self, self->unk_7F0);
    }
}

void func_ov004_0222a284(struct Pair *p, u8 a, u8 b)
{
    p->a = a;
    p->b = b;
}
