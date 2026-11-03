/* friend_code_entry_3: 3 functions, module ov133
 * mwccarm 1.2/base -O4,s
 * func_ov133_0229b9a8 @ 0x0229b9a8, 0x68 bytes, Thumb
 * func_ov133_0229b978 @ 0x0229b978, 0x30 bytes, Thumb
 * func_ov133_0229b958 @ 0x0229b958, 0x20 bytes, Thumb
 */

#include "types.h"

extern void func_ov002_0220a314(char *p);
extern void func_ov002_0220a2b4(char *p);
extern int func_ov133_0229ba84(char *self);
extern int func_ov133_0229ba34(char *self);
extern void func_ov002_0220a05c(char *p, int a, int b, int c, int d);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern void func_ov002_0220a1dc(void *);
extern void func_ov002_0220a164(void *);

void func_ov133_0229b9a8(char *self)
{
    int a;
    int b;

    if ((u8) (*(u8 *) (self + 0x9c) + 0xf3) <= 1) {
        func_ov002_0220a314(self + 0x11c);
    } else {
        func_ov002_0220a2b4(self + 0x11c);
    }
    a = func_ov133_0229ba84(self);
    b = func_ov133_0229ba34(self);
    func_ov002_0220a05c(self + 0x11c, a, b, 3, 1);
    *(u8 *) (self + 0x9b) = *(u8 *) (self + 0x8d);
    func_ov002_02208098((void *) self, 4);
}

void func_ov133_0229b978(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x9c) == 0xc) {
        func_ov002_02208098(self, 0x9);
    } else {
        func_ov002_0220a1dc(self + 0x11c);
        func_ov002_02208098(self, 0x5);
    }
}

int func_ov133_0229b958(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov002_0220a164(self + 0x11c);
    return (int) func_ov002_02208098(self, 0x6);
}
