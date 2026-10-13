/* func_ov002_0220b008 @ 0x0220b008, 0x44 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02138d6c(void *, int, int, void *, void *);
extern void func_ov002_0220b10c(void *);
extern void func_ov002_0220b3a4();
extern void func_ov002_0220b3c4();
extern void *data_ov002_0220bd08;

void *func_ov002_0220b008(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov002_0220bd08;
    func_02138d6c(self + 0x4, 0x2, 0x7c, (void *) func_ov002_0220b3c4, (void *) func_ov002_0220b3a4);
    func_ov002_0220b10c(self + 0xfc);
    *(u8 *) (self + 0x1c8) = 0x0;
    return self;
}
