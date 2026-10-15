/* func_ov004_02232c48 @ 0x02232c48, 0x294 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u8 func_020b65c4(void);
extern int func_020b67e8(int);
extern int func_020b6818(int);
extern int func_02060ee0(void *, int);
extern u16 *func_02061204(int, int *);
extern u16 *func_020611e8(int, int *);
extern int func_020b6694(int);
extern int func_020b66c4(int);
extern u8 *func_0207cec0(void *, int);
extern u8 func_0207f30c(u8 *);
extern u8 func_0207f300(u8 *);
extern int func_020b6744(int);
extern int func_020b6774(int);
extern u16 *func_020349e8(int);
extern u16 *func_020349b8(int);
extern void __register_global_object(u16 *, void *destructor, void *);
extern void func_020051b0(void *object);
extern char data_021ebcd4[];
extern char data_021e5a2c[];
extern int data_ov004_022589f4;
extern int data_ov004_022589f8;
extern u16 data_ov004_02258a6c[6];
extern u16 data_ov004_02258a18[6];
extern char data_ov004_02258ac0, data_ov004_02258ab4, data_ov004_02258a0c, data_ov004_02258a9c, data_ov004_02258a90,
    data_ov004_02258a60;
extern char data_ov004_02258a78, data_ov004_02258aa8, data_ov004_02258acc, data_ov004_02258a3c, data_ov004_02258a00,
    data_ov004_02258a24;

void func_ov004_02232c48(char *self, u16 *wall, int *outA, u16 *floor, int *outB)
{
    int k = func_020b65c4();
    *outB = 0;
    *outA = *outB;
    if (func_020b67e8(k) != 0) {
        int idx = func_02060ee0(data_021ebcd4, func_020b6818(k));
        if (idx == 0) {
            return;
        }
        *wall = *func_02061204(idx, outA);
        *floor = *func_020611e8(idx, outB);
        return;
    }
    if (func_020b6694(k) != 0) {
        u8 *p = func_0207cec0(data_021e5a2c, func_020b66c4(k));
        u8 a, b;
        if (p == 0) {
            return;
        }
        a = func_0207f30c(p);
        *wall = (a < 0x44) ? (u16) (a + 0x1100) : 0x1100;
        b = func_0207f300(p);
        *floor = (b < 0x44) ? (u16) (b + 0x1144) : 0x1144;
        return;
    }
    if (func_020b6744(k) == 0) {
        return;
    }
    {
        int slot = func_020b6774(k);
        u16 *pw = func_020349e8(k);
        int ok = 0;
        u16 w = *pw;
        u16 *pf;
        int ok2;
        u16 f;
        if (w >= 0x1100 && w <= 0x1143) {
            ok = 1;
        }
        if (ok != 0) {
            *wall = w;
        } else {
            if ((data_ov004_022589f4 & 1) == 0) {
                data_ov004_02258a6c[0] = 0x1140;
                __register_global_object(&data_ov004_02258a6c[0], ((void *) &func_020051b0), &data_ov004_02258ac0);
                data_ov004_02258a6c[1] = 0x1141;
                __register_global_object(&data_ov004_02258a6c[1], ((void *) &func_020051b0), &data_ov004_02258ab4);
                data_ov004_02258a6c[2] = 0x1142;
                __register_global_object(&data_ov004_02258a6c[2], ((void *) &func_020051b0), &data_ov004_02258a0c);
                data_ov004_02258a6c[3] = 0x1143;
                __register_global_object(&data_ov004_02258a6c[3], ((void *) &func_020051b0), &data_ov004_02258a9c);
                data_ov004_02258a6c[4] = 0x1143;
                __register_global_object(&data_ov004_02258a6c[4], ((void *) &func_020051b0), &data_ov004_02258a90);
                data_ov004_02258a6c[5] = 0x1143;
                __register_global_object(&data_ov004_02258a6c[5], ((void *) &func_020051b0), &data_ov004_02258a60);
                data_ov004_022589f4 |= 1;
            }
            *wall = data_ov004_02258a6c[slot];
        }
        pf = func_020349b8(k);
        ok2 = 0;
        f = *pf;
        if (f >= 0x1144 && f <= 0x1187) {
            ok2 = 1;
        }
        if (ok2 != 0) {
            *floor = f;
        } else {
            if ((data_ov004_022589f8 & 1) == 0) {
                data_ov004_02258a18[0] = 0x1184;
                __register_global_object(&data_ov004_02258a18[0], ((void *) &func_020051b0), &data_ov004_02258a78);
                data_ov004_02258a18[1] = 0x1185;
                __register_global_object(&data_ov004_02258a18[1], ((void *) &func_020051b0), &data_ov004_02258aa8);
                data_ov004_02258a18[2] = 0x1186;
                __register_global_object(&data_ov004_02258a18[2], ((void *) &func_020051b0), &data_ov004_02258acc);
                data_ov004_02258a18[3] = 0x1187;
                __register_global_object(&data_ov004_02258a18[3], ((void *) &func_020051b0), &data_ov004_02258a3c);
                data_ov004_02258a18[4] = 0x1187;
                __register_global_object(&data_ov004_02258a18[4], ((void *) &func_020051b0), &data_ov004_02258a00);
                data_ov004_02258a18[5] = 0x1187;
                __register_global_object(&data_ov004_02258a18[5], ((void *) &func_020051b0), &data_ov004_02258a24);
                data_ov004_022589f8 |= 1;
            }
            *floor = data_ov004_02258a18[slot];
        }
    }
}
