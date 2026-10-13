/* func_0204558c @ 0x0204558c, 0xe4 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

typedef struct {
    int x, z;
} Pt;

extern unsigned int func_0204e414(void);
extern unsigned short func_02045670(int unused, int id);
extern int func_020456b0(void *unused, Pt *p, int i, int ctx);
extern void func_02046024(int a, Pt *p, int r, int s, int a5, int a6, int a7, int a8, int a9, int a10);
extern int data_020ca67c[];
extern u8 data_020ca640[];

void func_0204558c(u8 *self, int b, int id)
{
    unsigned int ctx;
    int r;
    int n;
    int i;
    int t;
    int bb;
    int k;
    int tz;
    u8 *q;
    volatile u16 v0, v1, v2;
    Pt pt;
    Pt pt2;

    pt.x = 0;
    pt.z = 0;
    ctx = func_0204e414();
    if (ctx == 0) {
        return;
    }
    switch (id) {
        case 0xcc:
            n = 2;
            break;
        default:
            n = 3;
            break;
    }
    r = func_02045670((int) self, id);
    for (i = 0; i < n; i++) {
        v2 = *(u16 *) (self + 2);
        t = v2;
        v1 = (u16) t;
        k = data_020ca67c[i];
        bb = data_020ca640[k];
        v0 = (u16) t;
        pt.x = ((int) v0 >> 8) + ((bb >> 4) - 8);
        pt.z = (v1 & 0xff) + ((bb & 0xf) - 8);
        if (func_020456b0(self, &pt, i, ctx) != 0) {
            pt2.x = pt.x;
            pt2.z = pt.z;
            func_02046024((u8) b, &pt2, r, 0xfff1, 0, 0, 0, (u8) i, 0, -1);
            tz = pt.z;
            q = self + i * 2;
            q[7] = (u8) pt.x;
            q[6] = (u8) tz;
        } else {
            *(u16 *) (self + i * 2 + 6) = 0xffff;
        }
    }
    *(u16 *) (self + 0xc) = (u16) r;
}
