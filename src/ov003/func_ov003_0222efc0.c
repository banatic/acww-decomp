/* func_ov003_0222efc0 @ 0x0222efc0, 0x360 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} UnkStruct_0222efc0;

extern char data_ov003_022617bc[];
extern char *data_020ccf94;

extern int func_02073dd4(char *g, int a);
extern int func_020a7278(void);
extern int func_ov003_02235ce8(char *a, int i, int k, UnkStruct_0222efc0 *p, int m, int n);
extern int func_ov003_02235c34(char *a, int i, signed char *kd, int *n, int *m, u8 *msg);
extern void func_ov003_0222fe18(char *a, char *e, int k);
extern int func_ov003_0222ee10(char *a, char *e);
extern void func_ov003_0222fa20(char *a, char *e, int mode);
extern int func_ov003_0222ef80(char *a, char *e, int kd, int n, int m);
extern int func_020ba4e4(void);
extern int func_ov003_0222d248(int k, int r);
extern void func_ov003_0222f6b0(char *a, char *e, int f, int mode);
extern void func_020042c0(char *p, UnkStruct_0222efc0 *v);
extern void func_02073820(char *g);
extern void func_020737f0(char *g, u8 *p, int n);
extern void func_02073770(char *g, int a, int b);

void func_ov003_0222efc0(char *a)
{
    char *e;
    UnkStruct_0222efc0 *p204;
    UnkStruct_0222efc0 *p1d4;
    UnkStruct_0222efc0 *q;
    s16 *p242;
    UnkStruct_0222efc0 w;
    UnkStruct_0222efc0 w2;
    int state;
    char *g;
    int n, m;
    int neg;
    int v;
    int kk;
    signed char kd;
    u8 i;
    u8 msg;

    e = data_ov003_022617bc;
    n = 0;
    m = 0;
    i = 0;
    g = data_020ccf94;
    neg = -1;
    for (; i < 8; i++) {
        state = *(u8 *) (e + 0x250);
        if (func_02073dd4(g, *(int *) (g + 0x64)) != 0) {
            p204 = (UnkStruct_0222efc0 *) (e + 0x204);
            p1d4 = (UnkStruct_0222efc0 *) (e + 0x1d4);
            kd = neg;
            if (func_ov003_02235ce8(a, i, *(signed char *) (e + 0x24d), p1d4, *(u8 *) (e + 0x254), 1) != 0) {
                goto sw;
            }
            msg = 0;
            if (func_ov003_02235c34(a, i, &kd, &n, &m, &msg) == 0) {
                goto sw;
            }
            if (state == 0) {
                if (n > 1) {
                    if (kd >= 0) {
                        p204->x = n;
                        p204->z = m;
                        p1d4->x = p204->x;
                        p1d4->y = p204->y;
                        p1d4->z = p204->z;
                        *(signed char *) (e + 0x24d) = kd;
                        *(u8 *) (e + 0x248) = 1;
                        *(u8 *) (e + 0x249) = 0;
                        q = (UnkStruct_0222efc0 *) (e + 0x1c8);
                        q->x = p204->x;
                        q->y = p204->y;
                        q->z = p204->z;
                        *(u8 *) (e + 0x250) = 2;
                    }
                }
            } else if (msg == 0xff || n == 1) {
                if (kd == 0x1e) {
                    v = *(u8 *) (e + 0x251);
                    if (v == 9 || v == 0x11) {
                        goto sw;
                    }
                }
                func_ov003_0222fe18(a, e, 1);
            } else {
                if (p1d4->x != n || p1d4->z != m) {
                    p1d4->x = n;
                    p1d4->z = m;
                    q = (UnkStruct_0222efc0 *) (e + 0x1c8);
                    q->x = p204->x;
                    q->y = p204->y;
                    q->z = p204->z;
                }
                *(u8 *) (e + 0x254) = msg;
            }
        }
    sw:
        switch (state) {
            case 2:
                if (func_020a7278() == 0 && func_02073dd4(g, *(int *) (g + 0x64)) != 0) {
                    if (kd != *(signed char *) (e + 0x24d) && n > 0) {
                        func_ov003_0222fe18(a, e, 1);
                    } else if (func_ov003_0222ee10(a, e) != 0) {
                        func_ov003_0222fa20(a, e, 0);
                    }
                } else {
                    func_ov003_0222fa20(a, e, 0);
                }
                break;
            case 3:
                if (func_02073dd4(g, *(int *) (g + 0x64)) != 0) {
                    if (func_020a7278() == 0) {
                        if (func_ov003_0222ef80(a, e, kd, n, m) != 0) {
                            *(u8 *) (e + 0x251) = 0xa;
                            func_ov003_0222fe18(a, e, 1);
                        }
                    }
                    kk = *(signed char *) (e + 0x24d);
                    if (func_ov003_0222d248(kk, func_020ba4e4()) == 5) {
                        *(u8 *) (e + 0x246) = 0;
                    } else {
                        *(u8 *) (e + 0x246) = 1;
                    }
                }
                func_ov003_0222f6b0(a, e, i, 1);
                break;
            case 4:
                if (func_02073dd4(g, *(int *) (g + 0x64)) == 0) {
                    *(u8 *) (e + 0x251) = 0xa;
                    func_ov003_0222fe18(a, e, 1);
                } else if (func_020a7278() != 0) {
                    p242 = (s16 *) (e + 0x242);
                    p204 = (UnkStruct_0222efc0 *) (e + 0x204);
                    w.x = p204->x;
                    w.y = p204->y;
                    w.z = p204->z;
                    func_020042c0(e + 0x174, &w);
                    if (*(u8 *) (e + 0x254) != 0xff) {
                        *(u8 *) (e + 0x254) = 0xff;
                        i = i | 0x10;
                        p1d4 = (UnkStruct_0222efc0 *) (e + 0x1d4);
                        p1d4->x = 1;
                        p1d4->y = 1;
                        p1d4->z = 1;
                        p204 = (UnkStruct_0222efc0 *) (e + 0x204);
                        p204->x = 1;
                        p204->y = 1;
                        p204->z = 1;
                        func_02073820(g);
                        func_020737f0(g, &i, 1);
                        func_02073770(g, 0x30, 7);
                    }
                    *p242 = *p242 + 1;
                    if (*p242 > 0xc8) {
                        *(u8 *) (e + 0x251) = 0xa;
                        func_ov003_0222fe18(a, e, 1);
                    }
                } else {
                    p204 = (UnkStruct_0222efc0 *) (e + 0x204);
                    w2.x = p204->x;
                    w2.y = p204->y;
                    w2.z = p204->z;
                    func_020042c0(e + 0x174, &w2);
                    if (*(u8 *) (e + 0x254) == 0xff) {
                        *(u8 *) (e + 0x251) = 0xa;
                    }
                    if (*(u8 *) (e + 0x251) == 0xa) {
                        func_ov003_0222fe18(a, e, 1);
                    }
                }
                break;
        }
        e = e + 0x25c;
    }
}
