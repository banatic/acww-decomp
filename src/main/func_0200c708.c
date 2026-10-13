/* func_0200c708 @ 0x0200c708, 0xc8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

// Sibling of func_0200c4cc, which supplied every callee prototype.

extern void *data_020ccf94;

extern void func_0200c610(void *p);
extern void func_0200c5e0(void *p);
extern void func_0200c598(void *p);
extern void *func_020984fc(u32 v);
extern void func_02099740(void *p, int n);
extern void *func_0209984c(void *p);
extern void func_0205dc94(void *p, void *v);
extern void func_02010934(void *p);
extern void func_02079280(void);
extern int func_02073908(void *p, u32 v);
extern void func_0200f164(void *p);
extern void func_0200f1a4(void *p, int n, u16 h);

void func_0200c708(u8 *self)
{
    u8 *s = self + 0x7d4;
    void *p;
    int v;

    if (*(u8 *) (s + 0xc) == 0) {
        switch (*(u32 *) (s + 4)) {
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
                if (p != 0) {
                    func_02099740(p, 0);
                    func_0205dc94(self + 0x70d, func_0209984c(p));
                    func_02010934(self);
                    func_02079280();
                }
                break;
        }
    }
    if (func_02073908(data_020ccf94, *(u32 *) (self + 0x800)) == 0) {
        return;
    }
    switch (*(u32 *) (s + 4)) {
        case 0:
            v = 0;
            break;
        case 1:
            v = 1;
            break;
        case 2:
            v = 2;
            break;
        case 3:
            func_0200f164(self);
            return;
        default:
            return;
    }
    func_0200f1a4(self, v, *(u16 *) s);
}
