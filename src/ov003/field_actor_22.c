/* field_actor_22: 6 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02211cbc @ 0x02211cbc, 0x2 bytes, Thumb
 * func_ov003_02211c20 @ 0x02211c20, 0x9c bytes, Thumb
 * func_ov003_02211ac0 @ 0x02211ac0, 0x160 bytes, Thumb
 * func_ov003_02211a4c @ 0x02211a4c, 0x74 bytes, Thumb
 * func_ov003_022119f0 @ 0x022119f0, 0x5c bytes, Thumb
 * func_ov003_022119d8 @ 0x022119d8, 0x18 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;

struct S7d4 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
};

struct UnkStruct_02211c20_2 {
    char pad_00[0x8e];
    short unk_8E;
    char pad_90[0x704 - 0x90];
    int unk_704;
    char pad_708[0x7d4 - 0x708];
    struct S7d4 unk_7D4;
    char pad_7E4[0x800 - 0x7e4];
    void *unk_800;
};

struct UnkStruct_02211c20 {
    Vec a, b, c, d;
};

typedef struct {
    int x;
    int y;
    int z;
} Vec_02211ac0;

struct UnkStruct_02211ac0_2 {
    char pad_00[0x8e];
    short unk_8E;
    char pad_90[0x2d8 - 0x90];
    int unk_2D8;
    char pad2[0x704 - 0x2dc];
    int unk_704;
    char pad_708[0x7d4 - 0x708];
    struct S7d4 unk_7D4;
    char pad_7E4[0x800 - 0x7e4];
    void *unk_800;
};

struct UnkStruct_02211ac0 {
    short h;
    char pad2[2];
    int sp4;
    int sp8;
    Vec_02211ac0 a;
    Vec_02211ac0 b;
    Vec_02211ac0 c;
    Vec_02211ac0 d;
};

struct UnkStruct_02211a4c {
    char pad_00[0x2d0];
    char unk_2D0;
    char pad_2D1[0x704 - 0x2d0 - 1];
    int unk_704;
    char pad_708[0x7d4 - 0x704 - 4];
    unsigned char unk_7D4;
    char pad_7D5[0x7f0 - 0x7d4 - 1];
    int unk_7F0;
    char pad_7F4[0x7fc - 0x7f0 - 4];
    int unk_7FC;
};

typedef struct UnkStruct_022119f0 {
    unsigned int pad_00;
    unsigned int v[3];
} UnkStruct_022119f0;

typedef struct UnkStruct_022119f0_2 {
    unsigned char pad_00[0x7d4];
    UnkStruct_022119f0 sub;
    unsigned char pad_7E4[0x800 - 0x7e4];
    unsigned int unk_800;
} UnkStruct_022119f0_2;

extern int func_02073908(void *, void *);
extern int func_0200f290(void *, int);
extern void func_0200f268(void *, int);
extern int func_ov003_02221294(void *, void *, int);
extern int func_ov003_02220f40(void *, void *, int);
extern unsigned char data_020ccf94[];
extern int func_020912d4(int, void *, void *, int);
extern int func_0200f328(void *, int);
extern unsigned int *func_0200f27c(void *, int);
extern void func_0204f818(int *, int *, void *);
extern int func_02030db8(int, int);
extern void func_02010f5c(void *);
extern int func_02056f94(void *);
extern void func_020109a0(void *, int b, int c, unsigned short d);
extern int func_02008258(void *, int);
extern int func_0200d4e8(void *, int, int, int);
extern int func_0201100c(void *self);
extern int func_0200f434(void *self, unsigned int *arr);
extern void func_02010d64(void *self);

void func_ov003_02211cbc(void *receiver, int event) {}

void func_ov003_02211c20(struct UnkStruct_02211c20_2 *o)
{
    struct UnkStruct_02211c20 t;
    struct S7d4 *p;
    if (func_02073908(*(void **) data_020ccf94, o->unk_800) != 0) {
        return;
    }
    if (func_0200f290(o, 0x1c) == 0) {
        return;
    }
    p = &o->unk_7D4;
    t.a.x = p->unk_04;
    t.a.y = p->unk_08;
    t.a.z = p->unk_0C;
    if (o->unk_704 == 0x4b) {
        t.b.x = t.a.x;
        t.b.y = t.a.y;
        t.b.z = t.a.z;
        func_ov003_02221294(o->unk_800, &t.b, 0);
    } else {
        t.c.x = t.a.x;
        t.c.y = t.a.y;
        t.c.z = t.a.z;
        func_ov003_02220f40(o->unk_800, &t.c, o->unk_8E);
        t.d.x = t.a.x;
        t.d.y = t.a.y;
        t.d.z = t.a.z;
        func_ov003_02221294(o->unk_800, &t.d, 0);
    }
    func_0200f268(o, 0x1c);
}

void func_ov003_02211ac0(struct UnkStruct_02211ac0_2 *o)
{
    struct UnkStruct_02211ac0 t;
    struct S7d4 *p;
    int x;
    int y;
    int z;
    int *f704_ptr;
    if ((*(&o->unk_704)) != 0x49) {
        p = &o->unk_7D4;
        x = p->unk_04;
        t.a.x = x;
        y = p->unk_08;
        t.a.y = y;
        z = p->unk_0C;
        t.a.z = z;
        t.h = o->unk_8E;
        if ((*(&o->unk_704)) == 0x4b) {
            switch ((int) ((((u32) o->unk_2D8) << 4) >> 16)) {
                case 2:
                    func_020912d4(6, &t.a, 0, 0);
                    break;

                case 5:
                    func_0200f328(o, 0x841);
                    func_0200f27c(o, 9);
                    break;

                case 7:
                    func_020912d4(7, &t.a, &t.h, 0);
                    t.b.x = t.a.x;
                    t.b.y = t.a.y;
                    t.b.z = t.a.z;
                    func_ov003_02221294(o->unk_800, &t.b, 0);
                    func_0200f268(o, 0x1c);
                    func_0204f818(&t.sp4, &t.sp8, &t.a);
                    func_02030db8(t.sp4, t.sp8);
                    break;
            }

        } else {
            switch ((int) ((((u32) o->unk_2D8) << 4) >> 16)) {
                case 5:
                    func_0200f328(o, 0x85b);
                    func_0200f27c(o, 9);
                    break;

                case 12:
                    func_020912d4(6, &t.a, 0, 0);
                    break;

                case 18:
                    func_020912d4(8, &t.a, &t.h, 0);
                    break;

                case 21:
                    t.c.x = x;
                    t.c.y = y;
                    t.c.z = z;
                    func_ov003_02220f40(o->unk_800, &t.c, (short) o->unk_8E);
                    t.d.x = t.a.x;
                    t.d.y = t.a.y;
                    t.d.z = t.a.z;
                    func_ov003_02221294(o->unk_800, &t.d, 0);
                    func_0200f328(o, 0x85c);
                    func_0200f268(o, 0x1c);
                    break;
            }
        }
    }
    func_02010f5c(o);
}

void func_ov003_02211a4c(struct UnkStruct_02211a4c *this)
{
    if (func_02056f94(&this->unk_2D0) != 0) {
        if (this->unk_704 == 0x49) {
            if (this->unk_7D4 != 0) {
                func_020109a0(this, 0x4e, 3, 0);
            } else {
                func_020109a0(this, 0x4b, 3, 0);
            }
        } else {
            this->unk_7FC = func_02008258(this, this->unk_7F0);
            func_0200d4e8(this, 3, 1, -1);
        }
    }
}

void func_ov003_022119f0(UnkStruct_022119f0_2 *self)
{
    func_ov003_02211ac0((struct UnkStruct_02211ac0_2 *) self);

    if (func_02073908((void *) ((*(unsigned int *) data_020ccf94)), (void *) self->unk_800) != 0) {
        func_0201100c(self);
    } else {
        UnkStruct_022119f0 *p = &self->sub;
        unsigned int arr[3];
        arr[0] = p->v[0];
        arr[1] = p->v[1];
        arr[2] = p->v[2];
        func_0200f434(self, arr);
    }

    func_02010d64(self);
    func_ov003_02211a4c((struct UnkStruct_02211a4c *) self);
}

void func_ov003_022119d8(void *dst, const void *src, unsigned short a, unsigned char b)
{
    *(unsigned int *) dst = *(const unsigned int *) src;
    *(unsigned int *) ((char *) dst + 4) = *(const unsigned int *) ((const char *) src + 4);
    *(unsigned int *) ((char *) dst + 8) = *(const unsigned int *) ((const char *) src + 8);
    *(unsigned short *) ((char *) dst + 0xc) = a;
    *(unsigned char *) ((char *) dst + 0xe) = b;
}
