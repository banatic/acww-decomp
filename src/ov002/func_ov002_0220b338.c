/* func_ov002_0220b338 @ 0x0220b338, 0x1e bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov002_0220b29c(void *, int);
extern void func_ov002_0220b358(void *);

int func_ov002_0220b338(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov002_0220b358(self);
    *(u8 *) (self + 0x75) = 0x0;
    return func_ov002_0220b29c(self, 0x1);
}
