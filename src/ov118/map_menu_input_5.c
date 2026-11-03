/* map_menu_input_5: 9 functions, module ov118
 * mwccarm 1.2/base -O4,s
 * func_ov118_0229bb00 @ 0x0229bb00, 0x48 bytes, Thumb
 * func_ov118_0229babc @ 0x0229babc, 0x44 bytes, Thumb
 * func_ov118_0229ba98 @ 0x0229ba98, 0x24 bytes, Thumb
 * func_ov118_0229ba60 @ 0x0229ba60, 0x38 bytes, Thumb
 * func_ov118_0229ba34 @ 0x0229ba34, 0x2c bytes, Thumb
 * func_ov118_0229b8c8 @ 0x0229b8c8, 0x16c bytes, Thumb
 * func_ov118_0229b8b0 @ 0x0229b8b0, 0x16 bytes, Thumb
 * func_ov118_0229b868 @ 0x0229b868, 0x48 bytes, Thumb
 * func_ov118_0229b834 @ 0x0229b834, 0x34 bytes, Thumb
 */

#include "types.h"

extern int func_0208e484(void *);
extern int func_ov118_0229a4b8(void *);
extern void func_ov118_0229adf0(void *, int);
extern void func_ov118_0229a874(void *);
extern void func_ov118_0229a854(void *p);
extern int func_ov118_0229a460(void *p, unsigned int v);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);
extern int func_0208e930(void *);
extern void *func_0208e95c(void *ptr, int value);
extern void func_ov118_0229abe0(void *ptr);
extern void func_ov118_0229a440(void *, int);
extern u16 data_021fbe40[];
extern int func_ov002_02208014(void *receiver);
extern void func_ov118_0229a894(u8 *self);
extern int func_ov090_02299078(int a);
extern int func_ov090_02299098(int a);
extern int func_ov118_0229c438(u8 *self, int a);
extern int func_ov090_02298f84(int a);
extern void func_ov002_0220a254(u8 *p);
extern int func_ov118_0229b390(u8 *self);
extern int func_ov118_0229b088(u8 *self, int a, int b);
extern void func_ov002_0220a0b4(u8 *p, int a, int b);
extern void func_ov118_0229a92c(void *p);
extern void func_ov118_0229aa0c(int);
extern void func_ov002_02207fc0(int);
extern void func_ov118_0229afd4(void *param, int x);
extern void func_ov118_0229af64(void *param, int x);
extern void func_ov118_0229a8b4(void *param);

void func_ov118_0229b8b0(void *p);
void func_ov118_0229b834(void *param);

void func_ov118_0229bb00(unsigned char *obj)
{
    int ret;

    if (func_0208e484(obj + 0x6c0) == 0) {
        return;
    }
    ret = func_ov118_0229a4b8(obj);
    if (ret == 1) {
        return;
    }
    if (ret == 2) {
        func_ov118_0229adf0(obj, 0);
        obj[0xa3] = 0xff;
        func_ov118_0229a874(obj);
    } else {
        func_ov118_0229a874(obj);
    }
}

void func_ov118_0229babc(void *p)
{
    if (func_0208e484((char *) p + 0x6c0) != 0) {
        func_ov118_0229a854(p);
        if (func_ov118_0229a460(p, 0x800) != 0) {
            func_ov002_02208098(p, 0xa);
        } else {
            func_ov002_02208098(p, 3);
        }
    }
}

void func_ov118_0229ba98(void *arg)
{
    if (func_0208e930((char *) arg + 0x678)) {
        func_ov002_02208098(arg, 8);
    }
}

void func_ov118_0229ba60(void *param)
{
    unsigned short flag;
    void *self = param;

    flag = (*(unsigned short *) data_021fbe40);
    if ((flag & 1) == 0) {
        func_0208e95c((char *) self + 0x678, 3);
        func_ov002_02208098(self, 9);
    } else {
        func_ov118_0229abe0(self);
    }
}

void func_ov118_0229ba34(void *p)
{
    if (func_0208e930((void *) ((char *) p + 0x678))) {
        func_ov118_0229a874(p);
        func_ov118_0229a440(p, 0x1000);
    }
}

void func_ov118_0229b8c8(u8 *self)
{
    int trg;
    int x;
    int y;
    int held;
    int ox;
    int oy;
    // ENDDECLS

    if (func_ov002_02208014(self) != 0) {
        func_ov118_0229b8b0((void *) self);
        return;
    }
    trg = data_021fbe40[1];
    if ((trg & 1) != 0 && self[0xad] != 0xe) {
        func_ov118_0229a894(self);
        return;
    }
    if ((trg & 0x100) != 0) {
        func_ov118_0229c438(self, func_ov090_02299078(5));
        return;
    }
    if ((trg & 0x200) != 0) {
        func_ov118_0229c438(self, func_ov090_02299098(5));
        return;
    }
    ox = self[0xae];
    x = ox;
    oy = self[0xaf];
    y = oy;
    held = data_021fbe40[0];
    if ((held & 0x40) != 0) {
        y = oy - 4;
    } else if ((held & 0x80) != 0) {
        y = oy + 4;
    }
    if (y < 0x30) {
        self[0xac] = (u8) func_ov090_02298f84(ox);
        func_ov002_0220a254(self + 0x6c0);
        func_ov118_0229b834((void *) self);
        return;
    }
    if (y > 0xb0) {
        y = 0xb0;
    }
    if ((held & 0x20) != 0) {
        x = x - 4;
    } else if ((held & 0x10) != 0) {
        x = x + 4;
    }
    if (x < 0x18) {
        x = 0x18;
    } else if (x > 0x98) {
        if (y < 0x50) {
            self[0xac] = 9;
        } else {
            y = (y - 0x50) >> 4;
            if (y >= func_ov118_0229b390(self)) {
                y = func_ov118_0229b390(self) - 1;
            }
            y = y + 0xa;
            self[0xac] = (u8) y;
        }
        func_ov118_0229b834((void *) self);
        return;
    }
    if (x == ox && y == oy) {
        return;
    }
    self[0xae] = (u8) x;
    self[0xaf] = (u8) y;
    self[0xad] = (u8) func_ov118_0229b088(self, self[0xae], self[0xaf]);
    func_ov002_0220a0b4(self + 0x6c0, self[0xae], self[0xaf]);
}

void func_ov118_0229b8b0(void *p)
{
    func_ov118_0229a92c(p);
    func_ov002_02208098(p, 0);
}

void func_ov118_0229b868(int r0)
{
    func_0208e95c((void *) (r0 + 0x678), 1);
    func_ov118_0229aa0c(r0);
    func_ov002_02207fc0(r0);
    if (func_ov118_0229a460((void *) r0, 0x800) != 0) {
        func_ov002_02208098((void *) r0, 10);
    } else {
        func_ov002_02208098((void *) r0, 3);
    }
}

void func_ov118_0229b834(void *param)
{
    func_ov118_0229afd4(param, 0);
    func_ov118_0229af64(param, 0x0E);
    func_ov118_0229a440(param, 0x800);
    func_ov002_02208098(param, 3);
    func_ov118_0229a8b4(param);
}
