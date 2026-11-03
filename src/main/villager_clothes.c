/* villager_clothes: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0202e0a8 @ 0x0202e0a8, 0x20 bytes, Thumb
 * func_0202e094 @ 0x0202e094, 0x12 bytes, Thumb
 * func_0202e058 @ 0x0202e058, 0x3c bytes, Thumb
 * func_0202dfd0 @ 0x0202dfd0, 0x88 bytes, Thumb
 * func_0202df18 @ 0x0202df18, 0xb8 bytes, Thumb
 * func_0202df00 @ 0x0202df00, 0x16 bytes, Thumb
 * func_0202defc @ 0x0202defc, 0x4 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x28];
    unsigned short unk_28;
    char pad_2A[2];
    char unk_2C[4];
} func_0202e0a8_struct;

typedef struct {
    char pad_00[0x28];
    unsigned short unk_28;
    char pad_2A[0x2];
    unsigned int unk_2C;
} UnkStruct_0202e058;

typedef struct {
    unsigned short val;
} UnkStruct_0202dfd0;

typedef struct {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_0202dfd0_2;

typedef struct UnkStruct_0202df18_2 {
    u8 pad_00[0x28];
    u16 id;
} UnkStruct_0202df18_2;

typedef struct UnkStruct_0202df18 {
    u8 pad_00[0x148];
    int unk_148;
} UnkStruct_0202df18;

extern void *func_020b9e58(void *);
extern void *func_02082eec(void *);
extern void *func_02082ed4(void *arg);
extern int func_0208308c(void *);
extern void *func_02082e90(char *);
extern void func_0205d3d4(void *, void *, int, int, int);
extern void *func_02081500(int);
extern void func_0205d36c(void *, void *);
extern int func_0205d25c(void *);
extern int func_0203cfa8(unsigned int *);
extern int func_0204bcdc(void *);
extern int func_0204bc64(void *);
extern int func_020b9d3c(UnkStruct_0202df18_2 *, int, int, int, int, int);
extern int data_020d8d2c;
extern void func_020b9e2c(void *);
extern void func_02083068(void *);

int func_0202df18(UnkStruct_0202df18_2 *a, UnkStruct_0202df18 *b, u16 *c);

void *func_0202e0a8(func_0202e0a8_struct *self)
{
    func_020b9e58(self);
    self->unk_28 = 0xfff1;
    func_02082eec((void *) self->unk_2C);
    return self;
}

void *func_0202e094(void *arg)
{
    func_02082ed4((char *) arg + 0x2c);
    return arg;
}

int func_0202e058(UnkStruct_0202e058 *a, int b, int c)
{
    a->unk_28 = 0xFFFF;
    if (func_0208308c(&a->unk_2C) == 0) {
        return 0;
    }
    if (func_0202df18((UnkStruct_0202df18_2 *) a, (UnkStruct_0202df18 *) b, (u16 *) c) == 0) {
        return 0;
    }
    return 1;
}

int func_0202dfd0(char *a, UnkStruct_0202dfd0_2 *b, UnkStruct_0202dfd0 *c)
{
    void *p;
    int flag;
    int v;
    int result;

    p = func_02082e90(a + 0x2c);
    result = 0;
    if (p != 0) {
        flag = result;
        if (c->val >= 0x11a8 && c->val <= 0x12a7) {
            flag = 1;
        }
        if (flag == 1) {
            func_0205d3d4(p, c, 0, 1, 1);
        } else {
            if (b->unk_830 != 0) {
                func_0205d36c(p, func_02081500(b->unk_830));
            } else {
                func_0205d3d4(p, c, 0, 1, 1);
            }
        }
        v = func_0205d25c(p);
        if (v != 0) {
            result = func_0203cfa8((unsigned int *) v);
        }
    }
    return result;
}

static __inline int same_(UnkStruct_0202df18_2 *a, u16 *c)
{
    int t;
    if (func_0204bcdc(c) != 0) {
        t = func_0204bc64(c);
        if (t == func_0204bc64(&a->id)) {
            return 1;
        }
        return 0;
    }
    if (*c == a->id) {
        return 1;
    }
    return 0;
}

int func_0202df18(UnkStruct_0202df18_2 *a, UnkStruct_0202df18 *b, u16 *c)
{
    int ret;
    int r;
    unsigned int ok;

    ret = 0;
    if (same_(a, c) != 0) {
        ok = 0;
        if (*c >= 0x12a8 && *c <= 0x12af) {
            ok = 1;
        }
        if (ok == 0) {
            goto end;
        }
        ok = 0;
        if (a->id >= 0x12a8 && a->id <= 0x12af) {
            ok = 1;
        }
        if (ok == 0) {
            goto end;
        }
    }
    r = func_0202dfd0((char *) a, (UnkStruct_0202dfd0_2 *) b, (UnkStruct_0202dfd0 *) c);
    if (r != 0) {
        ret = func_020b9d3c(a, b->unk_148, data_020d8d2c, r, 0, 0);
        a->id = *c;
    }
end:
    return ret;
}

void func_0202df00(void *arg0)
{
    void *r4;
    r4 = arg0;
    func_020b9e2c(r4);
    r4 = (char *) r4 + 0x2c;
    func_02083068(r4);
}

int func_0202defc(int p0)
{
    return ((int) (p0) + (40));
}
