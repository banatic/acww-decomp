/* func_ov002_0220b280 @ 0x0220b280, 0x10 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_ov002_0220ba54;

int func_ov002_0220b280(char *self)
{
    // DECLS
    // ENDDECLS
    return *(u8 *) ((char *) &data_ov002_0220ba54 + *(u8 *) (self + 0x75));
}
