/* func_ov003_0222a634 @ 0x0222a634, 0x150 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

extern char data_ov003_0225f76c[];
extern u8 data_ov003_0223c014[];
extern int data_020ccf94;
extern char *func_02060924(void);
extern int func_02073d90(int g);
extern int func_ov003_0222a578(Vec3 *v, int h, int owner, int kind);
extern int func_ov003_0222a558(void);
extern int func_ov003_0222799c(char *p, Vec3 *v, int a, int b, int c);
extern int func_ov003_0222791c(int a, int b);
extern void func_020604fc(char *p, char *self);
extern void func_ov003_0222a544(void);

int func_ov003_0222a634(char *self)
{
    int ret;
    Vec3 b;
    Vec3 a;
    char *p;
    int g;
    int owner;
    // P
    char *rec;
    int ok;
    int i;
    // /P
    ret = 0;
    p = func_02060924();
    if (p == 0) {
        return 0;
    }
    g = data_020ccf94;
    if (func_02073d90(g)) {
        int v = *(int *) (p + 0x3c);
        if (v < 0) {
            return 0;
        }
        owner = *(int *) (g + 0x64);
        if (v != owner) {
            return 0;
        }
    } else {
        owner = 0;
    }
    rec = data_ov003_0225f76c;
    ok = 1;
    for (i = 0; i < 6; i++) {
        if (self != rec && owner == *(s8 *) (rec + 0x227)) {
            ok = 0;
            break;
        }
        rec += 0x24c;
    }
    if (ok) {
        Vec3 *q = (Vec3 *) (self + 0x120);
        a.x = q->x;
        a.y = q->y;
        a.z = q->z;
        if (func_ov003_0222a578(&a, *(short *) (self + 0x138), owner, *(s8 *) (self + 0x7e))) {
            int t = (data_ov003_0223c014[*(u8 *) (self + 0x1ff) * 0x14] << 12) / 100;
            Vec3 *r = (Vec3 *) (p + 8);
            b.x = r->x;
            b.y = r->y;
            b.z = r->z;
            if (func_ov003_0222a558() && func_ov003_0222799c(self + 0x120, &b, t, t, t)) {
                if (*(u8 *) (self + 0x200) != 2) {
                    *(u8 *) (self + 0x200) = 2;
                }
                *(short *) (self + 0x138) = *(short *) (self + 0x138) + (short) func_ov003_0222791c(0x5000, 0x7fff);
                *(short *) (self + 0x140) = 0x14;
            } else {
                *(s8 *) (self + 0x227) = owner;
                *(int *) (self + 0x22c) = (int) p;
                func_020604fc(p, self);
                ret = 1;
                *(u8 *) (self + 0x23c) = 1;
            }
        }
        func_ov003_0222a544();
    }
    return ret;
}
