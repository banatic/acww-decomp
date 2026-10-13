/* func_ov004_0223a1e8 @ 0x0223a1e8, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_0223a5e4(void *);
extern void *data_0213efe8;
extern void *data_0213f020;
extern void *data_ov004_02255e74;

void *func_ov004_0223a1e8(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0223a5e4(self);
    *(void **) (self) = &data_ov004_02255e74;
    *(void **) (self + 0x1fc) = &data_0213efe8;
    *(void **) (self + 0x1fc) = &data_0213f020;
    *(u8 *) (self + 0x211) = 0x2;
    return self;
}
