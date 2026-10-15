/* func_ov050_02261d28 @ 0x02261d28, 0x1a8 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

extern "C" {

extern int func_020984e8(void);
extern int func_02099640(int argument0);
extern int func_02099020(int, int);
extern int func_ov050_02260510(int);
extern unsigned long strlen(const char *);
extern int strncmp(const char *, const char *, unsigned long);
extern void func_0206844c(int, u8 *, void *);

extern char data_ov050_02265824[];
extern char data_ov050_02265804[];
}

typedef struct {
    int a;
    int b;
} MP;
typedef struct {
    int key;
    MP fn;
} Entry;

extern "C" {
extern int data_ov050_02265ecc;
extern Entry data_ov050_022659bc[];
extern MP data_ov050_02265650, data_ov050_02265668, data_ov050_022656d0;
extern MP data_ov050_02265730, data_ov050_02265770, data_ov050_022655c8;
extern MP data_ov050_022655c0, data_ov050_022655b8, data_ov050_022655b0;
extern MP data_ov050_02265788, data_ov050_022655a0, data_ov050_02265760;
extern MP data_ov050_02265750;
}

class UnkStruct_02261d28 {
  public:
    char unk_04[0x1a];
    u8 unk_1E;
    char pad_1F[0x21];
    int unk_40;
    char pad_44[0x70];
    int unk_B4;
    char pad_B8[0x18];
    int unk_D0;
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
};

typedef void (*FN)(void *);

extern "C" void func_ov050_02261d28(UnkStruct_02261d28 *p);

void func_ov050_02261d28(UnkStruct_02261d28 *p)
{
    u8 m;
    unsigned int i;
    int f;
    int q;
    u8 *st;
    void *dp;

    q = func_020984e8();
    func_02099640(q);
    if (func_02099020(q, 1) != 0) {
        p->v42();
        return;
    }
    if (func_ov050_02260510(p->unk_B4) != 0 && strncmp(p->unk_04, data_ov050_02265824, strlen(data_ov050_02265824)) != 0) {
        return;
    }
    if (func_ov050_02260510(p->unk_B4) != 0) {
        dp = data_ov050_02265824;
    } else {
        dp = data_ov050_02265804;
    }

    p->unk_D0 = 0xff;
    f = data_ov050_02265ecc;
    if ((f & 1) == 0) {
        {
            int t0 = data_ov050_02265650.a, t1 = data_ov050_02265650.b;
            data_ov050_022659bc[0].fn.a = t0;
            data_ov050_022659bc[0].fn.b = t1;
        }
        {
            int t0 = data_ov050_02265668.a, t1 = data_ov050_02265668.b;
            data_ov050_022659bc[1].fn.a = t0;
            data_ov050_022659bc[1].fn.b = t1;
        }
        {
            int t0 = data_ov050_022656d0.a, t1 = data_ov050_022656d0.b;
            data_ov050_022659bc[2].fn.a = t0;
            data_ov050_022659bc[2].fn.b = t1;
        }
        {
            int t0 = data_ov050_02265730.a, t1 = data_ov050_02265730.b;
            data_ov050_022659bc[3].fn.a = t0;
            data_ov050_022659bc[3].fn.b = t1;
        }
        {
            int t0 = data_ov050_02265770.a, t1 = data_ov050_02265770.b;
            data_ov050_022659bc[4].fn.a = t0;
            data_ov050_022659bc[4].fn.b = t1;
        }
        {
            int t0 = data_ov050_022655c8.a, t1 = data_ov050_022655c8.b;
            data_ov050_022659bc[5].fn.a = t0;
            data_ov050_022659bc[5].fn.b = t1;
        }
        {
            int t0 = data_ov050_022655c0.a, t1 = data_ov050_022655c0.b;
            data_ov050_022659bc[6].fn.a = t0;
            data_ov050_022659bc[6].fn.b = t1;
        }
        {
            int t0 = data_ov050_022655b8.a, t1 = data_ov050_022655b8.b;
            data_ov050_022659bc[7].fn.a = t0;
            data_ov050_022659bc[7].fn.b = t1;
        }
        {
            int t0 = data_ov050_022655b0.a, t1 = data_ov050_022655b0.b;
            data_ov050_022659bc[8].fn.a = t0;
            data_ov050_022659bc[8].fn.b = t1;
        }
        {
            int t0 = data_ov050_02265788.a, t1 = data_ov050_02265788.b;
            data_ov050_022659bc[9].fn.a = t0;
            data_ov050_022659bc[9].fn.b = t1;
        }
        {
            int t0 = data_ov050_022655a0.a, t1 = data_ov050_022655a0.b;
            data_ov050_022659bc[10].fn.a = t0;
            data_ov050_022659bc[10].fn.b = t1;
        }
        {
            int t0 = data_ov050_02265760.a, t1 = data_ov050_02265760.b;
            data_ov050_022659bc[11].fn.a = t0;
            data_ov050_022659bc[11].fn.b = t1;
        }
        {
            int t0 = data_ov050_02265750.a, t1 = data_ov050_02265750.b;
            data_ov050_022659bc[12].fn.a = t0;
            data_ov050_022659bc[12].fn.b = t1;
        }
        data_ov050_02265ecc = f | 1;
    }

    i = 0;
    st = &p->unk_1E;
    for (; i < 0xd; i++) {
        int k = data_ov050_022659bc[i].key;
        if (k == *st) {
            MP *mp = &data_ov050_022659bc[i].fn;
            int d = mp->b;
            char *self = (char *) p + (d >> 1);
            FN g;
            if (d & 1) {
                g = *(FN *) (*(int *) self + mp->a);
            } else {
                g = (FN) mp->a;
            }
            g(self);
        }
    }

    if (p->unk_D0 != 0xff) {
        m = (u8) p->unk_D0;
        func_0206844c(p->unk_40, &m, dp);
    }
}
