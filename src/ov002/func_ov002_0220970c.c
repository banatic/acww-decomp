/* func_ov002_0220970c @ 0x0220970c, 0x34 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_0200277c(int, int);
extern void RtcSendPxiCommand(int);
extern void func_ov002_02208a04(void *, int);
extern void func_ov002_02208a0c(void *, int);

void func_ov002_0220970c(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0x17) = 0x1;
    func_0200277c(*(u8 *) (self + 0x1a), a1);
    if (a1 != 0x0) {
        func_ov002_02208a0c(self, 0x2);
    }
    RtcSendPxiCommand(0x13);
    func_ov002_02208a04(self, 0x10);
}
