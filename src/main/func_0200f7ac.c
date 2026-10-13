/* func_0200f7ac @ 0x0200f7ac, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

// Bitfield reads: bits 7-10 and 11-15 of a 16-bit word.
typedef struct UnkStruct_0200f7ac {
    u16 fa : 7;
    u16 fb : 4;
    u16 fc : 5;
} UnkStruct_0200f7ac;

extern void func_02099794(int b, UnkStruct_0200f7ac t);
extern u16 *func_0209d358(int z, int n);
extern int func_020112bc(void *a);
extern int func_0200ee0c(void *a);
extern UnkStruct_0200f7ac *func_0209627c(void);

void func_0200f7ac(void *a, int b, UnkStruct_0200f7ac *c)
{
    u16 *p;
    UnkStruct_0200f7ac *q;

    // T is passed by value.
    func_02099794(b, *c);
    p = func_0209d358(0, 0x50);
    // Parenthesised so the call term is added first.
    *p = (u16) (func_020112bc(a) + c->fb * 1000 + c->fc * 10);
    if (func_0200ee0c(a) == 0) {
        q = func_0209627c();
        *q = *c;
    }
}
