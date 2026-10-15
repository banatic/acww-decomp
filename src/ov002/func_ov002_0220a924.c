/* func_ov002_0220a924 @ 0x0220a924, 0x3c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_0208aa70(void *);
extern void func_ov002_0220aa20(char *self);
extern void func_ov002_0220b04c(void *);
extern void func_ov002_0220b06c(void *, int, int, int);

int func_ov002_0220a924(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    func_ov002_0220b04c(self + 0xfc);
    func_ov002_0220b06c(self + 0xfc, a1, 0x80, 0x2a);
    func_0208aa70(self + 0xfc);
    func_ov002_0220aa20(self);
    *(u8 *) (self + 0x1c8) = 0xc;
    return 0x1c8;
}
