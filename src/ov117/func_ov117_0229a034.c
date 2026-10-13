/* func_ov117_0229a034 @ 0x0229a034, 0xd8 bytes, Thumb, module ov117
 * mwccarm 1.2/base -O4,s
 */

/* FAKEMATCH: the empty if keeps the y load before the x shift; the plain copies shift x first */

#include "types.h"

extern void *func_0204e414(int);
extern void func_02060e78(void *);
extern int func_0204f3e4(void *, int *, int *, int *, int *, u16 *, u16 *, int, int);
extern void func_0204f800(int *, int *, int, int, int, int);
extern int func_0204f5e0(void *, int, int, int, int, int);
extern int func_020b3b50(int);
extern void func_020b3c58(int, int *, int *, int *, int *);
extern void func_ov117_0229a2a4(int, int, int, int, int);
extern int data_021ebcd4;
void func_ov117_0229a034(int param)
{
    u16 ids[2];
    int x;
    int y;
    int v0;
    int v1;
    int v2;
    int v3;
    int w0;
    int w1;
    int w2;
    int w3;
    void *p;
    int sx;
    int sy;
    int rx;
    int ry;
    int ret;
    int ret2;
    p = func_0204e414(param);
    if (p == 0) {
        return;
    }
    func_02060e78(&data_021ebcd4);
    ids[0] = 0x5014;
    ids[1] = 0x501a;
    if (func_0204f3e4(p, &v0, &v1, &v2, &v3, ids, &ids[1], 1, 0) == 0) {
        return;
    }
    func_0204f800(&x, &y, v0, v1, v2, v3);
    {
        int xv = x;
        int yv = y;
        sx = xv >> 4;
        sy = yv >> 4;
        if (((!ret) && (!ret)) && (!ret)) {
        }
        rx = xv - (sx << 4);
        ry = yv - (sy << 4);
    }
    ret = func_0204f5e0(p, sx, sy, rx, ry, 0);
    x = x * 2;
    y = y * 2;
    x += 1;
    y += 1;
    ret2 = func_020b3b50(ret);
    if (ret2 != 0) {
        func_020b3c58(ret2, &w0, &w1, &w2, &w3);
        x += w0 >> 11;
        y += w1 >> 11;
    }
    func_ov117_0229a2a4(param, 0xb, x, y, 0);
}
