/* func_0200e704 @ 0x0200e704, 0xf4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020961d0(u32);
extern void func_0205d0b8(void *, u8);
extern int func_02011340(void *);
extern void func_0205d058(void *, int);
extern void func_0205d4f0(void *, u8);
extern void func_0201131c(void *, void *);
extern void func_02010680(void *, void *);
extern int func_0205cfd4(void *);
extern int func_0205d25c(void *);
extern int func_0205f8b4(void *);
extern void func_0205d034(void *);
extern void func_020100d0(void *, int, int, void *, void *);
extern void func_020100b8(void *, int, int, void *, void *);
extern int func_021077e8(int);

extern const u8 data_020c75d8[];
extern const u8 data_020c75d0[];
extern int data_020d83e8;
extern int data_020d83f0;

void func_0200e704(unsigned char *self)
{
    struct {
        int x;
    } local;
    int a, b, c;

    func_0205d0b8(self + 0x389, data_020c75d8[func_020961d0(*(u32 *) (self + 0x800))]);

    if (func_02011340(self) == 0) {
        func_0205d058(self + 0x389, 0);
    } else {
        func_0205d058(self + 0x389, 1);
    }

    func_0205d4f0(self + 0x774, data_020c75d0[func_020961d0(*(u32 *) (self + 0x800))]);

    func_0201131c(&local, self);
    func_02010680(self, &local);

    a = func_021077e8(func_0205cfd4(self + 0x389));
    b = func_021077e8(func_0205d25c(self + 0x774));
    func_020100d0(self, b, a, &data_020d83e8, &data_020d83e8);
    func_020100b8(self, b, a, &data_020d83e8, &data_020d83e8);

    c = func_021077e8(func_0205f8b4(self + 0x7a0));
    func_020100b8(self, c, func_021077e8(func_0205cfd4(self + 0x389)), &data_020d83f0, &data_020d83f0);
    func_0205d034(self + 0x389);
}
