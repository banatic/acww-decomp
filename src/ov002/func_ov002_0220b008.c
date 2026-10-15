/* func_ov002_0220b008 @ 0x0220b008, 0x44 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void __cxa_vec_ctor(void *, int, int, void (*callback3)(void *), void (*callback4)(void *));
extern void *func_ov002_0220b10c(void *);
extern void *func_ov002_0220b3a4(char *arg0);
extern void *func_ov002_0220b3c4(char *arg0);
extern void *data_ov002_0220bd08;

#define DisposeElement_func_ov002_0220b3c4 ((void (*)(void *)) func_ov002_0220b3c4)

#define DisposeElement_func_ov002_0220b3a4 ((void (*)(void *)) func_ov002_0220b3a4)

void *func_ov002_0220b008(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov002_0220bd08;
    __cxa_vec_ctor(self + 0x4, 0x2, 0x7c, DisposeElement_func_ov002_0220b3c4, DisposeElement_func_ov002_0220b3a4);
    func_ov002_0220b10c(self + 0xfc);
    *(u8 *) (self + 0x1c8) = 0x0;
    return self;
}

#undef DisposeElement_func_ov002_0220b3c4
#undef DisposeElement_func_ov002_0220b3a4
