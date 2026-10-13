/* func_ov133_0229b978 @ 0x0229b978, 0x30 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov002_02208098(void *, int);
extern void func_ov002_0220a1dc(void *, int);

void func_ov133_0229b978(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x9c) == 0xc) {
        func_ov002_02208098(self, 0x9);
    } else {
        func_ov002_0220a1dc(self + 0x11c, *(u8 *) (self + 0x9c));
        func_ov002_02208098(self, 0x5);
    }
}
