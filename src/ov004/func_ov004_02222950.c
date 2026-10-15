/* func_ov004_02222950 @ 0x02222950, 0xe0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

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
