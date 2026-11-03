/* villager_talk_offers_2: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020290b0 @ 0x020290b0, 0x8c bytes, Thumb
 * func_02029074 @ 0x02029074, 0x3c bytes, Thumb
 * func_02028f5c @ 0x02028f5c, 0x118 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_02029074 UnkStruct_02029074;

typedef struct UnkStruct_02029074_2 UnkStruct_02029074_2;

struct UnkStruct_02029074 {
    char pad_00[0x830];
    unsigned int val;
};

struct UnkStruct_02029074_2 {
    char pad_00[0x100];
    UnkStruct_02029074 *ptr;
};

typedef struct UnkStruct_02028f5c {
    int a;
    int b;
} UnkStruct_02028f5c;

typedef struct L32 {
    u8 d[0x20];
    u8 a;
    u8 b;
    u8 pad_22[2];
} L32;

typedef struct UnkStruct_02028f5c_2 {
    int a;
    int b;
} UnkStruct_02028f5c_2;

typedef struct UnkStruct_02028f5c_3 {
    u8 pad_00[0x40];
    int unk_40;
    u8 pad_44[0x100 - 0x44];
    int unk_100;
    u8 pad_104[0x160 - 0x104];
    void *unk_160;
} UnkStruct_02028f5c_3;

extern void *func_020984e8(void);
extern int func_02099020(void *, int);
extern unsigned int func_0207b86c(void *, int, void *);
extern int func_0209bd10(unsigned int);
extern int func_0209bc94(unsigned int);
extern int func_020292b4(int, int, int, unsigned int);
extern int func_0202a1cc(int, int, int, unsigned int);
extern int func_0202913c(int, int, int, unsigned int);
extern int data_021e5a2c;
extern char *func_02137550(void *dst, unsigned int size);
extern unsigned int func_0208150c(unsigned int param);
extern int func_0207cb9c(void *ptr, unsigned int *buf, int num);
extern int data_021c29ec;
extern int data_021c1d6c;
extern UnkStruct_02028f5c_2 data_020d8db0;
extern int func_0207f270(void *q);
extern int func_020794d0(int);
extern int func_0209bbec(int h);
extern void *func_0209ad9c(void *r, int x);
extern unsigned int func_0207f1c8(void *q);
extern int func_0209b5ec(void *);
extern void func_0209e474(UnkStruct_02028f5c *s);
extern int func_0209b4d4(void *o);
extern int func_0209bd44(int x);
extern int func_0209bc40(int h);
extern int func_0209c330(int q);
extern int func_0209b484(int a, int b);
extern int func_0201cddc(int x);
extern int func_0207aa08(int *g, UnkStruct_02028f5c *s);
extern void func_0201cfb4(UnkStruct_02028f5c_3 *p, L32 *l);
extern void func_0201cf74(UnkStruct_02028f5c_3 *p, L32 *l, int n, void *a, void *b);
extern void func_0202d9d0(UnkStruct_02028f5c_3 *p, int h);
extern void func_0201cec8(UnkStruct_02028f5c_3 *p, L32 *l);
extern void func_0202da74(UnkStruct_02028f5c_3 *p, UnkStruct_02028f5c_2 c);
extern void func_02068388(int x, int n);
extern int data_020c8928[];
extern int data_020c8924[];

int func_020290b0(int a, int b, int c)
{
    int ret;
    void *x;
    unsigned int idx;

    x = func_020984e8();
    ret = 0;
    if (func_02099020(x, 1) == 0) {
        idx = func_0207b86c(&data_021e5a2c, b, x);
        if (idx < 0x16) {
            switch (func_0209bd10(idx)) {
                case 0:
                    ret = func_020292b4(a, b, c, idx);
                    break;
                case 1:
                    switch (func_0209bc94(idx)) {
                        case 0:
                            break;
                        case 1:
                            ret = func_0202a1cc(a, b, c, idx);
                            break;
                        case 3:
                            ret = func_0202913c(a, b, c, idx);
                            break;
                    }
                    break;
            }
        }
    }
    return ret;
}

int func_02029074(UnkStruct_02029074_2 *arg0)
{
    unsigned int local;
    func_02137550(&local, 4);
    local = func_0208150c(arg0->ptr->val);
    return func_0207cb9c(&data_021e5a2c, &local, 1);
}

int func_02028f5c(UnkStruct_02028f5c_3 *p, void *q, void *r)
{
    int v;
    UnkStruct_02028f5c s;
    L32 loc;
    int h;
    void *obj;
    int qq;

    h = func_020794d0((int) func_0207f270(q));
    obj = func_0209ad9c(r, func_0209bbec(h));
    qq = func_0209b5ec((void *) func_0207f1c8(q));
    s.a = 0;
    s.b = 0;
    func_0209e474(&s);
    if (obj != 0) {
        if (func_0209bd44(func_0209b4d4(obj)) == 0) {
            v = func_0209bc40(h);
            if (func_0209b484(v, func_0209c330(qq))) {
                if (func_0201cddc(p->unk_100) == 0xb) {
                    if (func_0207aa08(&data_021e5a2c, &s) == -1) {
                        if (func_02029074((UnkStruct_02029074_2 *) p)) {
                            func_0201cfb4(p, &loc);
                            p->unk_160 = obj;
                            func_0201cf74(p, &loc, 0, data_020c8928, &data_021c29ec);
                            func_0201cf74(p, &loc, 1, data_020c8924, &data_021c1d6c);
                            func_0202d9d0(p, h);
                            loc.a = 2;
                            loc.b = (u8) (loc.a - 1);
                            func_0201cec8(p, &loc);
                            func_0202da74(p, data_020d8db0);
                            func_02068388(p->unk_40, 1);
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}
