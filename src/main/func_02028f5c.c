/* func_02028f5c @ 0x02028f5c, 0x118 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

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

extern int data_021e5a2c;
extern int data_021c29ec;
extern int data_021c1d6c;
extern UnkStruct_02028f5c_2 data_020d8db0;

extern void func_0207f270(void *q);
extern int func_020794d0(void);
extern int func_0209bbec(int h);
extern void *func_0209ad9c(void *r, int x);
extern void func_0207f1c8(void *q);
extern int func_0209b5ec(void);
extern void func_0209e474(UnkStruct_02028f5c *s);
extern int func_0209b4d4(void *o);
extern int func_0209bd44(int x);
extern int func_0209bc40(int h);
extern int func_0209c330(int q);
extern int func_0209b484(int a, int b);
extern int func_0201cddc(int x);
extern int func_0207aa08(int *g, UnkStruct_02028f5c *s);
extern int func_02029074(UnkStruct_02028f5c_3 *p);
extern void func_0201cfb4(UnkStruct_02028f5c_3 *p, L32 *l);
extern void func_0201cf74(UnkStruct_02028f5c_3 *p, L32 *l, int n, void *a, void *b);
extern void func_0202d9d0(UnkStruct_02028f5c_3 *p, int h);
extern void func_0201cec8(UnkStruct_02028f5c_3 *p, L32 *l);
extern void func_0202da74(UnkStruct_02028f5c_3 *p, UnkStruct_02028f5c_2 c);
extern void func_02068388(int x, int n);

extern int data_020c8928[];
extern int data_020c8924[];

int func_02028f5c(UnkStruct_02028f5c_3 *p, void *q, void *r)
{
    int v;
    UnkStruct_02028f5c s;
    L32 loc;
    int h;
    void *obj;
    int qq;

    func_0207f270(q);
    h = func_020794d0();
    obj = func_0209ad9c(r, func_0209bbec(h));
    func_0207f1c8(q);
    qq = func_0209b5ec();
    s.a = 0;
    s.b = 0;
    func_0209e474(&s);
    if (obj != 0) {
        if (func_0209bd44(func_0209b4d4(obj)) == 0) {
            v = func_0209bc40(h);
            if (func_0209b484(v, func_0209c330(qq))) {
                if (func_0201cddc(p->unk_100) == 0xb) {
                    if (func_0207aa08(&data_021e5a2c, &s) == -1) {
                        if (func_02029074(p)) {
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
