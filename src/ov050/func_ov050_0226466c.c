/* func_ov050_0226466c @ 0x0226466c, 0xf8 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int *func_02095794(int);
extern int func_0201c378(void *, int);
extern int func_0201c2c8(void *, int);
extern int func_020e8b4c(s16, int);
extern int func_ov050_02260498(void *);
extern void func_0201b458(void *, void *, int *);
extern int func_020960f8(int, int);
extern int func_020eaa2c(void *, const void *);
extern void func_ov050_02264834(void *, int);
extern int func_ov050_022606b4(void *);
extern int func_ov050_022605c0(void *);
extern int func_ov050_02260528(void *);
extern int func_ov050_02260718(void *);
extern int func_020e8840(const void *);
int func_ov050_0226466c(void *self)
{
    int *p;
    int triple[3];
    unsigned short val;
    int local[4];
    int r6;
    int r7;
    int r4;
    int tmp;
    p = func_02095794(4);
    triple[0] = p[0];
    r4 = 2;
    triple[1] = p[1];
    triple[r4] = p[r4];
    r6 = func_0201c378(self, 4);
    tmp = func_0201c2c8(self, 4);
    r4 = func_020e8b4c(*((s16 *) (((u8 *) self) + 0x8e)), tmp);
    r7 = func_ov050_02260498(self);
    func_0201b458(local, self, triple);
    val = 0x8b;
    if (func_020960f8(val, 4) || func_020960f8(0x8c, 4)) {
        return 1;
    }
    if (r6 > r7 && func_020eaa2c(local, ((u8 *) self) + 0x5c) != 0) {
        func_ov050_02264834(self, 3);
    } else if (r4 > 0x2000) {
        func_ov050_02264834(self, 2);
    }
    if (func_ov050_022606b4(self) != 0) {
        return 1;
    }
    if (func_ov050_022605c0(self) != 0) {
        if (tmp) {
            return 1;
        } else {
            return 1;
        }
    }
    if (func_ov050_02260528(self) != 0) {
        return 1;
    }
    if (func_ov050_02260718(self) != 0) {
        return 1;
    }
    if ((*((u8 *) (((u8 *) self) + 0x72c))) != 0) {
        if (func_020e8840(((u8 *) self) + 0x72e) == 0) {
            func_ov050_02264834(self, 7);
        }
    }
    return 1;
}
