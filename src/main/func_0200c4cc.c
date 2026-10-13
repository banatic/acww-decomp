/* func_0200c4cc @ 0x0200c4cc, 0xcc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_0200f268(void *p, int n);
extern int func_02056f28(void *p, int n);
extern void func_0200f27c(void *p, int n);
extern void func_0200c610(void *p);
extern void func_0200c5e0(void *p);
extern void func_0200c598(void *p);
extern void *func_020984fc(u32 v);
extern void func_02099740(void *p, int n);
extern void *func_0209984c(void *p);
extern void func_0205dc94(void *p, void *v);
extern void func_02010bf0(void *p, const char *s, char *buf);
extern void func_02010bac(void *p, const char *s, char *buf);
extern void func_02079280(void);

extern unsigned char data_020d72fc[];
extern unsigned char data_020d7304[];

void func_0200c4cc(u8 *self)
{
    char buf[2];
    u32 idx;
    void *p;
    void *q;

    func_0200f268(self, 0xf);
    if (!func_02056f28(self + 0x2d0, 8)) {
        return;
    }
    func_0200f27c(self, 0xf);

    idx = *(u32 *) (self + 0x7d8);
    switch (idx) {
        case 0:
            func_0200c610(self);
            break;
        case 1:
            func_0200c5e0(self);
            break;
        case 2:
            func_0200c598(self);
            break;
        case 3:
            p = func_020984fc(*(u32 *) (self + 0x800));
            if (p == 0) {
                return;
            }
            func_02099740(p, 0);
            q = func_0209984c(p);
            func_0205dc94(self + 0x70d, q);
            buf[0] = *(u8 *) (self + 0x2e4);
            func_02010bf0(self, (const char *) data_020d72fc, buf);
            buf[1] = *(u8 *) (self + 0x2e4);
            func_02010bac(self, (const char *) data_020d7304, &buf[1]);
            func_02079280();
            break;
    }
}
