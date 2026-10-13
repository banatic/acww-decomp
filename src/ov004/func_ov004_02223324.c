/* func_ov004_02223324 @ 0x02223324, 0x64 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02019c20(void *, int, int, int, int, int);
extern void func_0201ad18(void *, int, int, int, void *, int, int, int);
extern void *data_020c80f8;
extern void *data_020c814c;
extern void *data_021fbee8;

int func_ov004_02223324(char *self)
{
    // DECLS
    // ENDDECLS
    func_0201ad18(self + 0x3b0, 0x0, 0x0, 0x0, &data_021fbee8, 0x4, *(int *) ((char *) &data_020c814c), 0x1);
    func_02019c20(self + 0x564, 0x1, 0xe4, 0x0, *(u16 *) ((char *) &data_020c80f8), *(u16 *) (self + 0x710));
    return 0x1;
}
