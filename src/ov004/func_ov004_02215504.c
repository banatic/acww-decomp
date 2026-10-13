/* func_ov004_02215504 @ 0x02215504, 0x198 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02215504 {
    int unk_00;
    u16 unk_04;
};

extern int func_ov004_0223cb10(void);
extern void *func_ov004_0223ca9c(int a, void *self);
extern void *func_ov004_0220e220(void *p);
extern struct UnkStruct_02215504 *func_ov004_0220da04(void *p, int i);
extern int func_ov004_0223cb20(void *o);
extern int func_ov004_0221078c(void *self);
extern void func_ov004_022101e4(void *self, int a, int b, int c, int d);
extern int func_ov004_0220ec8c(void *self);
extern void func_02095380(int v);

void func_ov004_02215504(char *self, int flag)
{
    void *o;
    int done;
    struct UnkStruct_02215504 *e;
    int r;

    o = func_ov004_0223ca9c(func_ov004_0223cb10(), self);
    done = 0;
    if (o != 0) {
        e = func_ov004_0220da04(func_ov004_0220e220(self + 0x6cc), done);
        if (*(int *) (self + 0x780) == 0x16) {
            if (func_ov004_0223cb20(o) == 2) {
                if (flag != 0) {
                    if (func_ov004_0221078c(self) != 0) {
                        done = 1;
                    }
                    func_ov004_022101e4(self, 0, 1, 0x1000, 0);
                } else {
                    if (func_ov004_0221078c(self) != 0) {
                        done = 1;
                    }
                    func_ov004_022101e4(self, 0, 3, 0x1000, (u16) (e->unk_04 - 1));
                }
            } else if (func_ov004_0223cb20(o) == 0) {
                if (flag != 0) {
                    if (func_ov004_0221078c(self) != 0) {
                        done = 1;
                    }
                    func_ov004_022101e4(self, 0, 3, 0x1000, (u16) (e->unk_04 - 1));
                } else {
                    if (func_ov004_0221078c(self) != 0) {
                        done = 1;
                    }
                    func_ov004_022101e4(self, 0, 1, 0x1000, 0);
                }
            }
        } else if (func_ov004_0223cb20(o) == 3) {
            if (flag != 0) {
                if (func_ov004_0221078c(self) != 0) {
                    done = 1;
                }
                func_ov004_022101e4(self, 0, 1, 0x1000, 0);
            } else {
                if (func_ov004_0221078c(self) != 0) {
                    done = 1;
                }
                func_ov004_022101e4(self, 0, 3, 0x1000, (u16) (e->unk_04 - 1));
            }
        } else if (func_ov004_0223cb20(o) == 1) {
            if (flag != 0) {
                if (func_ov004_0221078c(self) != 0) {
                    done = 1;
                }
                func_ov004_022101e4(self, 0, 3, 0x1000, (u16) (e->unk_04 - 1));
            } else {
                if (func_ov004_0221078c(self) != 0) {
                    done = 1;
                }
                func_ov004_022101e4(self, 0, 1, 0x1000, 0);
            }
        }
    }
    if (done == 0) {
        r = func_ov004_0220ec8c(self);
        if (r != 0xffff) {
            func_02095380(r);
        }
    }
}
