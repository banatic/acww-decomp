/* func_ov002_0220a8e8 @ 0x0220a8e8, 0x3c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_0208aa70(void *);
extern void func_ov002_0220aa20(void *);
extern void func_ov002_0220b04c(void *, int);
extern void func_ov002_0220b06c(void *, int, int, int);

int func_ov002_0220a8e8(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    func_ov002_0220b04c(self + 0xfc, a1);
    func_ov002_0220b06c(self + 0xfc, a1, 0x80, 0x12);
    func_0208aa70(self + 0xfc);
    func_ov002_0220aa20(self);
    *(u8 *) (self + 0x1c8) = 0xd;
    return 0x1c8;
}
