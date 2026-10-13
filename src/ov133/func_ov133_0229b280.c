/* func_ov133_0229b280 @ 0x0229b280, 0x2a bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov133_0229ad78(void *, int);
extern void func_ov133_0229b320(void *, int);

int func_ov133_0229b280(char *self)
{
    // DECLS
    int i;
    // ENDDECLS
    for (i = 0; i < 0xc; i++) {
        *(u8 *) (self + i + 0xa4) = 0xa;
    }
    func_ov133_0229b320(self, 0x0);
    return func_ov133_0229ad78(self, 0x8);
}
