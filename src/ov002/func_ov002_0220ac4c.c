/* func_ov002_0220ac4c @ 0x0220ac4c, 0x30 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov002_0220b338(void *, int);
extern void func_ov002_0220b36c(void *, void *, int, int);
extern void *data_ov002_0220bdc0;

int func_ov002_0220ac4c(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov002_0220b36c(self + 0x80, &data_ov002_0220bdc0, 0x6, 0x1);
    func_ov002_0220b338(self + 0x80, 0x21);
    *(u8 *) (self + 0x1c8) = 0x1;
    return 0x1c8;
}
