/* func_ov133_0229b2e4 @ 0x0229b2e4, 0x3a bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void RtcSendPxiCommand(int);
extern void func_ov133_0229ad78(void *, int);

void func_ov133_0229b2e4(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0x9f) = a1;
    *(u8 *) (self + 0xa1) = 0x10;
    if (*(u8 *) (self + 0xa2) != a1) {
        RtcSendPxiCommand(0x15);
    }
    *(u8 *) (self + 0xa2) = a1;
    func_ov133_0229ad78(self, 0x10);
}
