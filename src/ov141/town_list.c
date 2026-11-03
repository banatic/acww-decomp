/* town_list: 17 functions, module ov141
 * mwccarm 1.2/base -O4,s
 * func_ov141_0229a384 @ 0x0229a384, 0x20 bytes, Thumb
 * func_ov141_0229a358 @ 0x0229a358, 0x2c bytes, Thumb
 * func_ov141_0229a2c4 @ 0x0229a2c4, 0x94 bytes, Thumb
 * func_ov141_0229a280 @ 0x0229a280, 0x44 bytes, Thumb
 * func_ov141_0229a174 @ 0x0229a174, 0x10c bytes, Thumb
 * func_ov141_0229a0dc @ 0x0229a0dc, 0x98 bytes, Thumb
 * func_ov141_0229a028 @ 0x0229a028, 0xb4 bytes, Thumb
 * func_ov141_0229a004 @ 0x0229a004, 0x24 bytes, Thumb
 * func_ov141_02299fd0 @ 0x02299fd0, 0x34 bytes, Thumb
 * func_ov141_02299fcc @ 0x02299fcc, 0x2 bytes, Thumb
 * func_ov141_02299fc8 @ 0x02299fc8, 0x2 bytes, Thumb
 * func_ov141_02299f94 @ 0x02299f94, 0x34 bytes, Thumb
 * func_ov141_02299f7c @ 0x02299f7c, 0x18 bytes, Thumb
 * func_ov141_02299f6c @ 0x02299f6c, 0x10 bytes, Thumb
 * func_ov141_02299f5c @ 0x02299f5c, 0x10 bytes, Thumb
 * func_ov141_02299f1c @ 0x02299f1c, 0x40 bytes, Thumb
 * func_ov141_02299ee0 @ 0x02299ee0, 0x3c bytes, Thumb
 */

#include "types.h"

extern void func_ov002_0220a1dc(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov002_0220a164(void *);
extern int func_ov002_022088cc(int);
extern int sub_22088bc(int);
extern int func_ov002_022088bc(int);
extern int func_ov002_022088ac(int);
extern int func_ov002_0220889c(int);
extern int func_020b9bbc(char *a, char *b, int c, int d, int e);
extern int func_02074308(void);
extern int func_020ec148(void);
extern void func_020730c8(void);
extern int *func_020eb92c(void);
extern int func_020eb998(int);
extern int func_020eb9c4(int);
extern void MI_CpuCopy8(int, unsigned char *, int);
extern void func_ov139_022997c0(unsigned char *, int, unsigned char *);
extern void func_ov139_02299888(unsigned char *, int, unsigned char, int, int);
extern void func_ov139_02299798(unsigned char *, int);
extern void *func_ov002_0220afdc(void *p);
extern void *func_ov002_02209cb4(void *p);
extern void *func_ov139_02299b30(void *p);
extern void *func_ov002_0220826c(void *p);
extern void func_ov002_02207f6c(void *p);
extern unsigned char data_ov141_0229af48[];

void func_ov141_0229a0dc(unsigned char *self);
int func_ov141_0229a028(u8 *base, u8 *key);
int func_ov141_0229a004(const unsigned char *p);
void func_ov141_02299fd0(char *self, int idx, int param);
int func_ov141_02299f94(int *r0, int r1);
int func_ov141_02299f7c(unsigned short *base, unsigned int mask);
void func_ov141_02299f5c(unsigned short *p, unsigned short mask);

void func_ov141_0229a384(void *self)
{
    func_ov002_0220a1dc((char *) self + 0xa38);
    func_ov002_02208098((void *) (self), 3);
}

void func_ov141_0229a358(void *this)
{
    unsigned char *self = (unsigned char *) this;
    func_ov002_0220a164(self + 0xa38);
    self[0x1a7e] = self[0x8d];
    func_ov002_02208098((void *) (this), 4);
}

int func_ov141_0229a2c4(unsigned char *p, int arg)
{
    unsigned char orig;
    orig = p[0x1a8c];
    if (orig <= 5) {
        if (func_ov002_022088cc(arg)) {
            if (p[0x1a8c] != 0) {
                p[0x1a8c]--;
            }
        } else {
            if (func_ov002_022088bc(arg)) {
                if (p[0x1a8c] < 5) {
                    p[0x1a8c]++;
                } else {
                    p[0x1a8c] = 6;
                }
            }
        }
    } else {
        if (func_ov002_022088cc(arg)) {
            p[0x1a8c] = 5;
        } else if (func_ov002_022088ac(arg)) {
            p[0x1a8c] = 6;
        } else if (func_ov002_0220889c(arg)) {
            p[0x1a8c] = 7;
        }
    }
    if (orig != p[0x1a8c]) {
        return 1;
    } else {
        return 0;
    }
}

void func_ov141_0229a280(char *p)
{
    if (func_ov141_02299f7c((unsigned short *) p, 4)) {
        if (func_020b9bbc(p + 0xc68, p + 0x127c, 6, 0x800, 0)) {
            func_ov141_02299f5c((unsigned short *) p, 4);
        }
    }
}

void func_ov141_0229a174(unsigned char *self)
{
    int i;
    int a;
    int *array;
    int val, val2, val3, val4;
    int r7, ret, ext, ext2;
    unsigned char buffer[0x19];
    unsigned char r4;
    int item;
    unsigned char *ptr;

    func_02074308();
    a = func_020ec148();

    for (i = 0; i < 6; i++) {
        if ((self + i)[0x1a7f] == 1) {
            (self + i)[0x1a7f] = 2;
        }
    }

    func_020730c8();
    array = func_020eb92c();

    val2 = 0;
    val3 = 0;
    val4 = 0;
    r4 = 0;

    while (r4 < a) {
        item = array[r4];
        if (item != 0) {
            func_020730c8();
            r7 = func_020eb998(item);
            if (r7 == 0x1a) {
                func_020730c8();
                ext = func_020eb9c4(item);
                MI_CpuCopy8(ext, buffer, r7);
                if (buffer[0x18] == 0) {
                    ret = func_ov141_0229a028((u8 *) self, (u8 *) item);
                    if (ret == ~val3) {
                        r7 = func_ov141_0229a004((const unsigned char *) self);
                        if (r7 != ~val4) {
                            func_ov141_02299fd0((char *) self, r7, item);
                            func_020730c8();
                            val = func_020eb998(item);
                            func_020730c8();
                            ext2 = func_020eb9c4(item);
                            ptr = (self + 0x11cc) + r7 * 0x1a;
                            MI_CpuCopy8(ext2, ptr, val);
                            func_ov139_022997c0(self + 0x94, r7, ptr);
                            (self + r7)[0x1a85] = val2;
                        }
                    } else {
                        func_ov141_02299fd0((char *) self, ret, item);
                    }
                }
            }
        }
        r4 = (unsigned char) (r4 + 1);
    }

    func_ov141_0229a0dc(self);
}

void func_ov141_0229a0dc(unsigned char *self)
{
    int i;
    int a = -1;

    i = 0;
    do {
        switch (*(self + i + 0x1a7f)) {
            case 1:
                if (*(self + i + 0x1a85) < 5) {
                    *(self + i + 0x1a85) += 1;
                    func_ov139_02299888(self + 0x94, i, *(self + i + 0x1a85), 5, 14);
                }
                break;
            case 2:
                if (*(self + i + 0x1a85) > 1) {
                    *(self + i + 0x1a85) -= 1;
                    func_ov139_02299888(self + 0x94, i, *(self + i + 0x1a85), 5, 14);
                } else {
                    *(self + i + 0x1a7f) = 0;
                    func_ov139_02299798(self + 0x94, i);
                    if (*(int *) (self + 0x1270) == i) {
                        func_ov141_02299f94((int *) self, a);
                    }
                }
                break;
        }
        i++;
    } while (i < 6);
}

int func_ov141_0229a028(u8 *base, u8 *key)
{
    int i;
    int e5, e4, e3, e2, e1;
    u8 *e;

    for (i = 0; i < 6; i++) {
        if (*(base + i + 0x1a7f) != 2) {
            continue;
        }
        e5 = 0;
        e4 = 0;
        e3 = 0;
        e2 = 0;
        e1 = 0;
        e = base + 0xc8e + i * 0xe0;
        if (key[2] == e[0] && key[3] == e[1]) {
            e1 = 1;
        }
        if (e1 != 0) {
            if (key[4] == e[2]) {
                e2 = 1;
            }
        }
        if (e2 != 0) {
            if (key[5] == e[3]) {
                e3 = 1;
            }
        }
        if (e3 != 0) {
            if (key[6] == e[4]) {
                e4 = 1;
            }
        }
        if (e4 != 0) {
            if (key[7] == e[5]) {
                e5 = 1;
            }
        }
        if (e5 != 0) {
            return i;
        }
    }
    return -1;
}

int func_ov141_0229a004(const unsigned char *p)
{
    int i;
    for (i = 0; i < 6; i++) {
        const unsigned char *q = p + i;
        if (q[0x1a7f] == 0) {
            return i;
        }
    }
    return -1;
}

void func_ov141_02299fd0(char *self, int idx, int param)
{
    MI_CpuCopy8(param, (unsigned char *) (self + 0xc8c + 0xe0 * idx), 0xe0);
    ((char *) self + idx)[0x1a7f] = 1;
}

void func_ov141_02299fcc(void *receiver) {}

void func_ov141_02299fc8(void) {}

int func_ov141_02299f94(int *r0, int r1)
{
    int r2;
    int r3;

    r2 = (r0[0x49c] == r1) ? 0 : 1;
    r0[0x49c] = r1;
    if (r1 == -1) {
        r0[0x49d] = 9;
    } else {
        r0[0x49d] = 8;
    }
    return r2;
}

int func_ov141_02299f7c(unsigned short *base, unsigned int mask)
{
    if ((*(unsigned short *) ((char *) base + 0x1a7c) & mask) != 0) {
        return 1;
    }
    return 0;
}

void func_ov141_02299f6c(unsigned short *p, unsigned short val)
{
    unsigned short *q = (unsigned short *) ((char *) p + 0x1a7c);
    *q = *q | val;
}

void func_ov141_02299f5c(unsigned short *p, unsigned short mask)
{
    p = (unsigned short *) ((char *) p + 0x1a7c);
    *p &= ~mask;
}

void *func_ov141_02299f1c(void *self)
{
    *(void **) self = (void *) data_ov141_0229af48;
    func_ov002_0220afdc((char *) self + 0x0a9c);
    func_ov002_02209cb4((char *) self + 0x0a38);
    func_ov139_02299b30((char *) self + 0x94);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}

void *func_ov141_02299ee0(void *p)
{
    *(void **) p = (void *) ((char *) data_ov141_0229af48);
    func_ov002_0220afdc((char *) p + 0xA9C);
    func_ov002_02209cb4((char *) p + 0xA38);
    func_ov139_02299b30((char *) p + 0x94);
    func_ov002_0220826c(p);
    return p;
}
