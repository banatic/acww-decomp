/* field_actor_17: 9 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02210668 @ 0x02210668, 0x4 bytes, Thumb
 * func_ov003_02210660 @ 0x02210660, 0x6 bytes, Thumb
 * func_ov003_02210640 @ 0x02210640, 0x20 bytes, Thumb
 * func_ov003_02210634 @ 0x02210634, 0xc bytes, Thumb
 * func_ov003_022105ec @ 0x022105ec, 0x48 bytes, Thumb
 * func_ov003_02210504 @ 0x02210504, 0xe8 bytes, Thumb
 * func_ov003_02210474 @ 0x02210474, 0x90 bytes, Thumb
 * func_ov003_022103cc @ 0x022103cc, 0xa8 bytes, Thumb
 * func_ov003_0221038c @ 0x0221038c, 0x40 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    char pad_00[0x8e];
    unsigned char unk_8E;
    char pad_8F[0x2d8 - 0x8f];
    unsigned int unk_2D8;
    char pad_2DC[0x62c - 0x2dc];
    Vec3 unk_62C;
    char pad_638[0x7d4 - 0x638];
    int unk_7D4;
} UnkStruct_02210504;

typedef struct UnkStruct_02210474 UnkStruct_02210474;

struct UnkStruct_02210474 {
    unsigned char pad_00[0x2d0];
    unsigned int unk_2D0[2];
    unsigned int unk_2D8;
    unsigned char pad_2DC[0x4f8];
    int unk_7D4;
    unsigned char pad_7D8[0x18];
    int unk_7F0;
    unsigned char pad_7F4[0x8];
    int unk_7FC;
    unsigned char pad_800[0xf0];
    unsigned int unk_8F0[4];
};

typedef struct {
    unsigned char pad_00[0x2d0];
    unsigned char pad_2D0[0x504];
    int unk_7D4;
    unsigned char pad_7D8[0x18];
    unsigned int unk_7F0;
    unsigned char pad_7F4[0x8];
    unsigned int unk_7FC;
    unsigned int unk_800;
    unsigned char pad_804[0xec];
} UnkStruct_022103cc;

extern void func_020109a0(void *p, int b, int c, unsigned short d);
extern int func_ov003_0221066c(int a, int b, int c);
extern void func_0209129c(int param);
extern void func_0200fa6c(int *dest, void *src);
extern unsigned char data_ov003_02260540;
extern int data_ov003_02260558[3];
extern void func_02010f5c(void *self);
extern int func_0203f7d0(void *a, void *b);
extern int func_020912d4(int a, void *v, void *p, int d);
extern void func_02091278(void *, void *, void *, void *);
extern int func_0200f328(void *self, int a);
extern int func_0200ff28(void *self, void *v, int a, int b);
extern int func_02056f94(void *);
extern int func_02008258(UnkStruct_02210474 *, int);
extern int func_0200d4e8(UnkStruct_02210474 *, int, int, int);
extern int func_ov003_0220d268(UnkStruct_02210474 *);
extern int func_02096518(unsigned int *a, int b, unsigned int c);
extern void func_02010d64(char *p);
extern int func_02010ca4(char *p);
extern int func_02073908(int a, int b);
extern int data_020ccf94;

void func_ov003_02210668(unsigned char *p0, int p1)
{
    p0[0] = p1;
}

void func_ov003_02210660(u8 *src, u8 *dst)
{
    *dst = *src;
}

void func_ov003_02210640(void *obj, void *message, int previous)
{
    func_020109a0(obj, 0x61, 3, 0);
    *(int *) ((char *) obj + 0x7d4) = -1;
}

void func_ov003_02210634(int a, int b)
{
    func_ov003_0221066c(a, 6, b);
}

void func_ov003_022105ec(void *arg)
{
    int field;
    int local[3];

    field = *(int *) ((char *) arg + 0x7d4);
    if (field != -1) {
        func_0209129c(field);
    }
    func_0200fa6c(local, arg);
    data_ov003_02260540 = 0;
    data_ov003_02260558[0] = local[0];
    data_ov003_02260558[1] = local[1];
    data_ov003_02260558[2] = local[2];
}

void func_ov003_02210504(UnkStruct_02210504 *self)
{
    Vec3 v, a, b;
    int k;
    int *pid;
    int tx, ty, tz;

    func_02010f5c(self);
    k = (int) ((self->unk_2D8 << 4) >> 16);
    pid = &self->unk_7D4;
    if (k >= 5 && k <= 0x23) {
        tz = self->unk_62C.z;
        ty = self->unk_62C.y;
        tx = self->unk_62C.x;
        v.x = tx;
        v.y = ty;
        v.z = tz;
        func_0203f7d0(&v, &v);
        if (*pid == -1) {
            *pid = func_020912d4(0x26, &v, &self->unk_8E, 0);
            func_0200f328(self, 0x854);
            func_0200fa6c((int *) (&a), self);
            data_ov003_02260540 = 1;
            (*(Vec3 *) data_ov003_02260558).x = a.x;
            (*(Vec3 *) data_ov003_02260558).y = a.y;
            (*(Vec3 *) data_ov003_02260558).z = a.z;
        } else {
            func_02091278((void *) (*pid), (void *) (&v), (void *) (0), 0);
        }
        switch (k) {
            case 0x14:
                func_0200fa6c((int *) (&b), self);
                v.x = b.x;
                v.y = b.y;
                v.z = b.z;
                func_0200ff28(self, &v, 1, 5);
                break;
            case 0x23:
                if (*pid != -1) {
                    func_0209129c(*pid);
                    *pid = -1;
                }
                break;
        }
    }
}

void func_ov003_02210474(UnkStruct_02210474 *self)
{
    if (func_02056f94(self->unk_2D0) != 0) {
        self->unk_7FC = func_02008258(self, self->unk_7F0);
        func_0200d4e8(self, 3, 1, -1);
    }

    {
        void *sub2 = self->unk_8F0;
        func_ov003_02210668((unsigned char *) sub2, 0);
        if (((self->unk_2D8 << 4) >> 16) >= 0x21) {
            if (func_ov003_0220d268(self) != 0) {
                int *p = &self->unk_7D4;
                func_ov003_02210668((unsigned char *) sub2, 1);
                if (self->unk_7D4 != -1) {
                    func_0209129c(self->unk_7D4);
                    *p = -1;
                }
            }
        }
    }
}

void func_ov003_022103cc(UnkStruct_022103cc *self)
{
    unsigned char flag;
    unsigned int local;
    int *p;
    char *base;

    self->unk_7FC = func_02008258((UnkStruct_02210474 *) self, self->unk_7F0);

    base = (char *) self + 0x8f0;
    func_ov003_02210660((u8 *) base, (u8 *) (&flag));

    if (flag && func_02096518(&local, -1, self->unk_800) && local == 0x63) {
        func_ov003_0221066c((int) self, 6, -1);
        p = (int *) ((char *) self + 0x7d4);
        func_ov003_02210668((unsigned char *) base, 1);
        if (self->unk_7D4 != -1) {
            func_0209129c(self->unk_7D4);
            *p = -1;
        }
    } else {
        if (func_02056f94((char *) self + 0x2d0)) {
            func_0200d4e8((UnkStruct_02210474 *) self, 3, 1, -1);
        }
    }
}

void func_ov003_0221038c(char *p)
{
    func_ov003_02210504((UnkStruct_02210504 *) p);
    func_02010d64(p);
    func_02010ca4(p);
    if (func_02073908(data_020ccf94, *(int *) (p + 0x800)) != 0) {
        func_ov003_02210474((UnkStruct_02210474 *) p);
    } else {
        func_ov003_022103cc((UnkStruct_022103cc *) p);
    }
}
