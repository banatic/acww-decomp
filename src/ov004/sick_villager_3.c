/* sick_villager_3: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02222a88 @ 0x02222a88, 0x48 bytes, Thumb
 * func_ov004_02222a30 @ 0x02222a30, 0x58 bytes, Thumb
 * func_ov004_02222950 @ 0x02222950, 0xe0 bytes, Thumb
 */

#include "types.h"

extern void *func_020edf70(int size);
extern void *func_0202e8e4(void *p);
extern void *func_0202decc(void *p);
extern void func_02084f88(void *p);
extern int data_ov004_022541d8;
extern int data_ov004_02254148;
extern int func_0204bcdc(void *p);
extern int func_0204bc64(void *p);
extern int func_0202e364(char *self);
extern void func_0201c280(char *a, char *b);
extern void func_ov004_022226b4(char *a, char *b);
extern char *func_0207b410(void *p);
extern unsigned int func_ov004_0222271c(char *p);
extern void func_0201b388(char *p, int n);
extern void func_0201b38c(char *p, int n);
extern void func_0201af28(char *p, int a, int b, int c, int d);
extern void func_0201ad18(char *p, int a, int b, int c, int d, int e, int f, int g);
extern int func_ov004_02222178(char *self, int a);
extern char *data_ov004_02257f7c;
extern int data_021e5a2c;
extern int data_020c814c;
extern unsigned char data_021fbee8[];

void *func_ov004_02222a88(void)
{
    char *p = (char *) func_020edf70(0xa94);
    if (p != 0) {
        func_0202e8e4(p);
        *(int *) p = (int) &data_ov004_022541d8;
        func_0202decc(p + 0x8a0);
        *(int *) (p + 0x8a0) = (int) &data_ov004_02254148;
        func_02084f88(p + 0xa54);
    }
    return p;
}

int func_ov004_02222a30(unsigned short *p, int flag)
{
    unsigned short local;
    int t1, t2;
    unsigned int cond;

    if (flag == 0) {
        if (func_0204bcdc(p) != 0) {
            local = 0x155e;
            t1 = func_0204bc64(p);
            t2 = func_0204bc64(&local);
            cond = (t1 == t2) ? 1 : 0;
        } else {
            cond = (*p == 0x155e) ? 1 : 0;
        }
        if (cond != 0) {
            return 1;
        }
    }
    return 0;
}

int func_ov004_02222950(char *self)
{
    // DECLS
    // ENDDECLS

    if (func_0202e364(self) == 0) {
        return 0;
    }
    data_ov004_02257f7c = self;
    func_0201c280(self, self + 0x8a0);
    func_ov004_022226b4(self + 0x8a0, self);
    self[0xa44] = *(u8 *) (func_0207b410(&data_021e5a2c) + 0xba);
    if (func_ov004_0222271c(self + 0x8a0) > 1) {
        func_0201b388(self + 0x2a0, 0xea);
        func_0201b38c(self + 0x2a0, 0xe9);
        func_0201af28(self + 0x350, 1, 0xa4, 0x10, 0x10);
        func_0201ad18(self + 0x3b0, 0, 0, 0, (unsigned int) data_021fbee8, 4, data_020c814c, 1);
        self[0x897] = 1;
    } else {
        func_0201af28(self + 0x350, 1, 0xcd, 0x14, 0x14);
        self[0x897] = 0;
    }
    func_ov004_02222178(self, 0);
    return 1;
}
