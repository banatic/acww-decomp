/* func_ov050_022643dc @ 0x022643dc, 0x134 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u16 data_020c80f8;

extern int func_020960f8(int a, int b);
extern void func_ov050_02264834(void *self, int a);
extern int func_ov050_022606b4(void *self);
extern int func_ov050_022605c0(void *self);
extern int func_ov050_02260528(void *self);
extern int func_ov050_02260718(void *self);
extern void *func_02095794(int a);
extern int func_0201c378(void *self, int a);
extern void func_0201b458(void *buf, void *self, void *tmp);
extern int func_ov050_02260498(void *self);
extern int func_ov050_02260474(void *self);
extern int func_02019e00(void *p);
extern int func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern void func_0201b044(void *p, void *buf);
extern int func_020eaa6c(void *buf, void *p);

int func_ov050_022643dc(char *self)
{
    int tmp[3];
    int buf[4];
    int *p;
    int r4;
    int r6;

    if (func_020960f8(0x8b, 4) != 0 || func_020960f8(0x8c, 4) != 0) {
        func_ov050_02264834(self, 1);
        return 1;
    }

    if (func_ov050_022606b4(self) != 0) {
        return 1;
    }
    if (func_ov050_022605c0(self) != 0) {
        return 1;
    }
    if (func_ov050_02260528(self) != 0) {
        return 1;
    }
    if (func_ov050_02260718(self) != 0) {
        return 1;
    }

    p = (int *) func_02095794(4);
    tmp[0] = p[0];
    tmp[1] = p[1];
    tmp[2] = p[2];

    r4 = func_0201c378(self, 4);
    func_0201b458(buf, self, tmp);
    r6 = func_ov050_02260498(self);

    if (r4 > func_ov050_02260474(self)) {
        if (func_02019e00(self + 0x564) == 1) {
            func_02019d0c(self + 0x564, 2, 1, 0, 0, 0x800, 0, 0, 0, data_020c80f8, 0);
        }
    } else {
        if (func_02019e00(self + 0x564) == 2) {
            func_02019d0c(self + 0x564, 1, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        }
    }

    func_0201b044(self + 0x350, buf);

    if (r4 <= r6 || func_020eaa6c(buf, self + 0x5c) != 0) {
        func_ov050_02264834(self, 1);
    }

    return 1;
}
