/* func_ov004_022399ec @ 0x022399ec, 0x194 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;
typedef struct {
    u8 bytes[17];
} Descriptor;
extern Descriptor data_ov004_02247924[];
#define W(p, o) (*(int *) ((p) + (o)))
#define S(p, o) (*(short *) ((p) + (o)))
extern int func_ov004_02239460(int, int), func_ov004_0223938c(Vec *, int), func_ov004_02239858(void *);
extern int func_ov004_02239bb4(Vec *, int, int);
extern void func_ov004_02239944(void *, int, int, int);
extern void func_ov004_022398a8(void *, int);
void func_ov004_022399ec(u8 *self)
{
    Vec pos;
    if (self[0x1ee] == 1) {
        return;
    }
    if (!self[0x1fd]) {
        if (func_ov004_02239460(0, 100) < 75) {
            self[0x1fd] = 1;
        } else {
            self[0x1fd] = 2;
            return;
        }
    } else if (self[0x1eb] >= 4) {
        self[0x1fd] = 1;
        self[0x1fc] = 0;
        self[0x1eb] = 0;
    }
    if (self[0x1fd] == 1) {
        if (self[0x1ee] == 5) {
            self[0x1ee] = 4;
        }
        if (!self[0x1fc]) {
            pos.x = W(self, 0x1a8);
            pos.y = W(self, 0x1ac);
            pos.z = W(self, 0x1b0);
            func_ov004_02239bb4(&pos, (data_ov004_02247924[W(self, 0x15c)].bytes[3] << 12) >> 7, S(self, 0x1c0));
            func_ov004_02239944(self, func_ov004_0223938c(&pos, S(self, 0x1c0)), 2, 6);
            self[0x1fc] = 1;
            S(self, 0x250) = 0;
            S(self, 0x250) += S(self, 0x200);
        }
        if (S(self, 0x200) * S(self, 0x250) < 0) {
            if (func_ov004_02239858(self)) {
                self[0x1fd] = 2;
            } else if (self[0x1c6] == 0) {
                self[0x1fd] = 2;
            } else if (self[0x1c6] == 1 && !self[0x22e]) {
                self[0x1fd] = 2;
            }
        } else {
            self[0x22f] = 0;
            S(self, 0x1c0) += S(self, 0x200);
            S(self, 0x250) += S(self, 0x200);
            func_ov004_022398a8(self, (u16) * (signed char *) (self + 0x1fe));
            if (self[0x1ee] == 4) {
                W(self, 0x158) = 0;
            }
        }
    } else if (self[0x1fd] == 2) {
        func_ov004_02239858(self);
    }
}
