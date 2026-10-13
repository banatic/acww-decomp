/* func_ov004_0222585c @ 0x0222585c, 0x68 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_0201b388(void *, int);
extern int func_0201b38c(void *, int);
extern void func_0201c280(void *, void *);
extern void func_0201c3f4(void *, int);
extern int func_0202edc8(void *);
extern int func_020b65c4(int);
extern void func_ov004_02225470(void *, void *);

int func_ov004_0222585c(char *self)
{
    // DECLS
    // ENDDECLS
    if (func_0202edc8(self) == 0x0) {
        return 0x0;
    } else {
        func_0201c280(self, self + 0x658);
        func_ov004_02225470(self + 0x658, self);
        func_0201c3f4(self, 0x100);
        func_0201b388(self + 0x2a0, 0xd9);
        if (func_020b65c4(func_0201b38c(self + 0x2a0, 0xd8)) != 0xb) {
            *(u8 *) (self + 0x563) = 0x1;
        }
        return 0x1;
    }
}
