/* func_ov003_0222db40 @ 0x0222db40, 0x26c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} UnkStruct_0222db40;
typedef struct {
    char pad_00[0x204];
} UnkStruct_0222db40_2;

extern char data_ov003_022617bc[];
extern char data_ov003_02260bf0[];
extern char *data_020ccf94;
extern s16 FX_SinCosTable_[];

extern void func_ov003_0222d1bc(UnkStruct_0222db40_2 *d, int k);
extern void func_ov003_0222cf1c(UnkStruct_0222db40_2 *d);
extern void func_ov003_0222c4b8(UnkStruct_0222db40_2 *d, int wx, int wz, int rx, u8 up, u8 dn);
extern void *func_020961a8(int n);
extern int func_02073dd4(char *g, int a);
extern int func_02096614(u8 *f, int *y, int *z, int neg, int i);
extern char *func_ov003_02236164(int n);
extern int func_ov003_0221ac18(char *o);
extern int func_ov003_02233c70(int a, int b);
extern int func_020ea990(UnkStruct_0222db40 *a, UnkStruct_0222db40 *b);
extern int FX_MulFunc(int a, int b);
extern s16 func_0200322c(UnkStruct_0222db40 *a, UnkStruct_0222db40 *b);
extern int func_ov003_0222ff2c(char *a, char *e);
extern int func_ov003_0222cf60(char *e, UnkStruct_0222db40_2 *d, int id, int p2);

int func_ov003_0222db40(char *a, int id, int p2, int mode)
{
    UnkStruct_0222db40_2 d;
    char *e;
    char *g;
    UnkStruct_0222db40 *p204;
    UnkStruct_0222db40 *q;
    UnkStruct_0222db40 *p;
    char *obj;
    UnkStruct_0222db40 *r6;
    UnkStruct_0222db40 *src;
    UnkStruct_0222db40 *dst;
    unsigned int k;
    char *t;
    unsigned int n;
    int idx;
    int neg;
    int ang;
    int len;
    u8 flag;
    int yy, zz;
    int j;
    int slot;

    e = data_ov003_022617bc;
    slot = ~0;
    if (id != 8) {
        func_ov003_0222d1bc(&d, p2);
    } else {
        func_ov003_0222cf1c(&d);
    }
    if (mode == 1) {
        k = 0;
        while (k < 8) {
            if (*(u8 *) (e + 0x248) != 0) {
                if (id != 0x33) {
                    p204 = (UnkStruct_0222db40 *) (e + 0x204);
                    if (id == 0x23) {
                        if (*(signed char *) (e + 0x24d) == 0x23) {
                            return 0;
                        }
                    }
                    if (id != 8) {
                        func_ov003_0222c4b8(&d, p204->x, p204->z, 1, 1, 1);
                    }
                }
            } else if (slot < 0) {
                slot = (signed char) k;
            }
            e = e + 0x25c;
            k = (u8) (k + 1);
        }
    }
    if (slot >= 0 || mode == 2) {
        t = (char *) func_020961a8(4);
        if (t != 0 && mode == 1 && id != 0x33) {
            g = data_020ccf94;
            if (func_02073dd4(g, *(int *) (g + 0x64)) != 0) {
                neg = -1;
                for (j = 0; j < 4; j++) {
                    if (func_02096614(&flag, &yy, &zz, neg, j) != 0) {
                        if (flag == 0) {
                            func_ov003_0222c4b8(&d, yy, zz, 5, 8, 5);
                        }
                    }
                }
            } else {
                q = (UnkStruct_0222db40 *) (t + 0x5c);
                func_ov003_0222c4b8(&d, q->x, q->z, 5, 8, 5);
            }
        }
        if (mode == 1) {
            e = data_ov003_022617bc + slot * 0x25c;
        } else {
            e = data_ov003_02260bf0;
        }
        if (id == 0x23) {
            g = data_020ccf94;
            if (func_02073dd4(g, *(int *) (g + 0x64)) == 0) {
                n = 0;
                while (n < 2) {
                    obj = func_ov003_02236164(n);
                    if (obj != 0) {
                        p = (UnkStruct_0222db40 *) (obj + 0x5c);
                        r6 = (UnkStruct_0222db40 *) (e + 0x204);
                        ang = func_ov003_0221ac18(obj);
                        len = func_ov003_02233c70(0x20, 1);
                        if (t != 0) {
                            if (func_020ea990((UnkStruct_0222db40 *) (t + 0x5c), p) > 0xc000) {
                                r6->x = p->x;
                                r6->y = p->y;
                                r6->z = p->z;
                                idx = ((u16) len >> 4) * 2;
                                r6->x = r6->x + FX_MulFunc(FX_SinCosTable_[idx], ang);
                                r6->z = r6->z + FX_MulFunc(FX_SinCosTable_[idx + 1], ang);
                                *(s16 *) (e + 0x23a) = func_0200322c(p, r6);
                                *(u8 *) (e + 0x248) = 1;
                                *(u8 *) (e + 0x24d) = (u8) id;
                                *(u8 *) (e + 0x249) = 0;
                                *(int *) (e + 0x21c) = n;
                                func_ov003_0222ff2c(a, e);
                                return 1;
                            }
                        }
                    }
                    n = (u8) (n + 1);
                }
                goto zero;
            }
        }
        if (func_ov003_0222cf60(e, &d, id, p2) != 0) {
            *(u8 *) (e + 0x248) = 1;
            *(u8 *) (e + 0x24d) = (u8) id;
            *(u8 *) (e + 0x249) = 0;
            src = (UnkStruct_0222db40 *) (e + 0x204);
            dst = (UnkStruct_0222db40 *) (e + 0x1c8);
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
            if (mode == 1) {
                func_ov003_0222ff2c(a, e);
            }
            return 1;
        }
    }
zero:
    return 0;
}
