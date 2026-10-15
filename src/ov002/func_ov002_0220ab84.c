/* func_ov002_0220ab84 @ 0x0220ab84, 0x38 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov002_0220b338(char *self, int value);
extern void func_ov002_0220b36c(void *, void *, int, int);
extern void *data_ov002_0220be08;

int func_ov002_0220ab84(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    func_ov002_0220b36c(self + 0x80, &data_ov002_0220be08, 0x6, 0x2);
    func_ov002_0220b338(self + 0x80, (u8) a1);
    *(u8 *) (self + 0x1c8) = 0x5;
    return 0x1c8;
}
