/* fox_tent: 7 functions, module ov052
 * mwccarm 1.2/base -O4,s
 * func_ov052_02260880 @ 0x02260880, 0x34 bytes, Thumb
 * func_ov052_02260854 @ 0x02260854, 0x2c bytes, Thumb
 * func_ov052_02260718 @ 0x02260718, 0x13c bytes, Thumb
 * func_ov052_02260574 @ 0x02260574, 0x1a4 bytes, Thumb
 * func_ov052_02260554 @ 0x02260554, 0x20 bytes, Thumb
 * func_ov052_022604ec @ 0x022604ec, 0x68 bytes, Thumb
 * func_ov052_022604a0 @ 0x022604a0, 0x4c bytes, Thumb
 */

#include "types.h"

#define OBJ ((UnkStruct_02260718 *) (a + 0x658))

typedef struct UnkStruct_02260718 UnkStruct_02260718;

struct Vt {
    void (*unk_00)(UnkStruct_02260718 *);
    void (*unk_04)(UnkStruct_02260718 *);
    void (*unk_08)(UnkStruct_02260718 *);
};

struct UnkStruct_02260718 {
    struct Vt *vt;
};

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_02260574_3 {
    char pad_00[0x618];
    int unk_618;
    char pad1[0x71e - 0x61c];
    u16 unk_71E;
    char pad_720[0x728 - 0x720];
    int unk_728;
    int unk_72C;
    u8 unk_730;
} UnkStruct_02260574_3;

typedef struct UnkStruct_02260574 {
    char pad_00[0x5c];
    Vec3 unk_5C;
    char pad1[0x8e - 0x68];
    u16 unk_8E;
} UnkStruct_02260574;

typedef struct {
    u16 a;
    u16 b;
} UnkStruct_02260574_2;

typedef struct {
    unsigned char data[0x800];
} SelfType;

extern int func_02014868(void *);
extern int func_0201c014(void *);
extern void func_ov052_02261908(void *, int);
extern int func_0201c2a4(void *, int);
extern void func_02016108(UnkStruct_02260718 *, int);
extern int func_ov052_022610c4(UnkStruct_02260718 *);
extern int *func_02095794(int);
extern int func_02030818(int *);
extern int func_020307f8(void);
extern int func_020b5e10(void);
extern int func_020b6098(int, int);
extern UnkStruct_02260574 *func_020961a8(int);
extern int func_0203ec98(void);
extern int FX_MulFunc(int, int);
extern void func_0204f818(int *, int *, Vec3 *);
extern int func_ov004_0223cd50(void);
extern int func_ov004_0223cc10(int, int, int, int);
extern int func_020b6590(void);
extern int func_020b7524(int, int, int);
extern int func_020b758c(int, Vec3 *);
extern u16 *func_ov004_02246378(int, int);
extern int func_0204bcdc(u16 *);
extern int func_0204bc64(u16 *);
extern u8 data_021f6c38;
extern u8 data_021f6c34;
extern UnkStruct_02260574_2 data_021fbe40;
extern short FX_SinCosTable_[];
extern void func_ov052_022610cc(void *ptr, int arg);
extern int func_0203e0a8(void *self, int arg);
extern void func_0209e474(void *);

int func_ov052_02260554(int param);

int func_ov052_02260880(void *p)
{
    if (func_02014868((char *) p + 0x618) != 0 || func_0201c014(p) != 0 || func_ov052_02260554((int) p) != 0) {
        return 0;
    }
    return 1;
}

int func_ov052_02260854(void *p)
{
    if (func_02014868((char *) p + 0x618) != 0) {
        goto ret0;
    }
    if (func_0201c014(p) == 0) {
        goto ret1;
    }
ret0:
    return 0;
ret1:
    return 1;
}

void func_ov052_02260718(char *a, unsigned int cmd, int v)
{
    int t[3];

    a[0x560] = (char) v;
    switch (cmd) {
        case 3:
            func_ov052_02261908(a, 8);
            break;
        case 1:
            OBJ->vt->unk_08(OBJ);
            func_02016108(OBJ, func_0201c2a4(a, 4));
            if (func_ov052_022610c4(OBJ) == 0) {
                func_ov052_02261908(a, 5);
                break;
            }
            if (func_ov052_022610c4(OBJ) == 1 || func_ov052_022610c4(OBJ) == 2 || func_ov052_022610c4(OBJ) == 0xc) {
                func_ov052_02261908(a, 6);
            } else {
                func_ov052_02261908(a, 9);
            }
            break;
        case 0:
            OBJ->vt->unk_08(OBJ);
            func_02016108(OBJ, func_0201c2a4(a, 4));
            func_ov052_02261908(a, 5);
            break;
        case 8:
            if (func_ov052_022610c4(OBJ) == 1 || func_ov052_022610c4(OBJ) == 2) {
                int *p = func_02095794(4);
                int rc;
                t[0] = p[0];
                t[1] = p[1];
                t[2] = p[2];
                rc = func_02030818(t);
                if (rc) {
                    func_020307f8();
                } else {
                    func_ov052_02261908(a, 1);
                }
            } else if (func_ov052_022610c4(OBJ) == 0xc) {
                func_020b6098(func_020b5e10(), 0);
            } else {
                func_ov052_02261908(a, 1);
            }
            break;
    }
}

int func_ov052_02260574(UnkStruct_02260574_3 *self)
{
    u16 sent[2];
    UnkStruct_02260574 *o;
    Vec3 *sp5c;
    int x, z;
    int x2, z2;
    Vec3 v;
    Vec3 v2;
    unsigned int a;
    unsigned int b;
    int r;
    int t;
    int ok;
    u16 h;
    int i;

    o = func_020961a8(4);
    if (data_021f6c38 != 0 && data_021f6c34 != 0) {
        a = 1;
    } else {
        a = 0;
    }
    if (a != 0) {
        b = 1;
    } else {
        b = 0;
    }

    if (o == 0 || func_0203ec98() != 0 || func_02014868(&self->unk_618) != 0 || ((data_021fbe40.b & 1) == 0 && b == 0)) {
        return 0;
    }

    sp5c = &o->unk_5C;
    v.x = sp5c->x;
    v.y = sp5c->y;
    v.z = sp5c->z;
    h = o->unk_8E;
    x = 0;
    z = 0;
    i = (h >> 4) * 2;
    v.x = v.x + FX_MulFunc(0x2000, FX_SinCosTable_[i]);
    v.z = v.z + FX_MulFunc(0x2000, FX_SinCosTable_[i + 1]);
    func_0204f818(&x, &z, &v);

    if (b != 0) {
        r = func_ov004_0223cc10(func_ov004_0223cd50(), x, z, 0);
        if (r != 0) {
            if (r != func_020b7524(func_020b6590(), 0, 0)) {
                return 0;
            }
        } else {
            x2 = 0;
            z2 = 0;
            func_020b758c(func_020b6590(), &v2);
            func_0204f818(&x2, &z2, &v2);
            if (x2 != x || z2 != z) {
                return 0;
            }
        }
    }

    sent[0] = *func_ov004_02246378(x, z);
    if (func_0204bcdc(&sent[0]) != 0) {
        sent[1] = 0xfff1;
        t = func_0204bc64(&sent[0]);
        if (t == func_0204bc64(&sent[1])) {
            ok = 1;
        } else {
            ok = 0;
        }
    } else {
        ok = (sent[0] == 0xfff1) ? 1 : 0;
    }
    if (ok != 0) {
        return 0;
    }

    self->unk_71E = sent[0];
    self->unk_728 = x;
    self->unk_72C = z;
    self->unk_730 = 0;
    return 1;
}

int func_ov052_02260554(int param)
{
    int result;
    if (func_ov052_02260574((UnkStruct_02260574_3 *) ((void *) param)) != 0) {
        func_0203e0a8((void *) param, 0);
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

int func_ov052_022604ec(SelfType *self)
{
    void *result;
    unsigned int local[3];

    result = (void *) func_02095794(4);
    local[0] = ((unsigned int *) result)[0];
    local[1] = ((unsigned int *) result)[1];
    local[2] = ((unsigned int *) result)[2];

    if (func_02030818((int *) local) != 0) {
        if (self->data[0x732] == 0) {
            func_ov052_022610cc((char *) self + 0x658, 1);
        } else {
            func_ov052_022610cc((char *) self + 0x658, 2);
        }

        func_0203e0a8(self, 0);
        func_ov052_02261908(self, 0xa);

        return 1;
    }

    return 0;
}

int func_ov052_022604a0(void *self)
{
    int buf[2];

    if (func_0203ec98() != 0) {
        return 0;
    }
    buf[0] = 0;
    buf[1] = 0;
    func_0209e474(buf);
    if (((unsigned char *) buf)[2] < 6) {
        func_ov052_022610cc((char *) self + 0x658, 0xc);
        func_0203e0a8(self, 0);
        return 1;
    }
    return 0;
}
