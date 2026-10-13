/* func_ov133_0229bb78 @ 0x0229bb78, 0x3c bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov002_02208098(void *, int);
extern void func_ov002_0220b9b8(void *, void *, int, int);
extern int func_ov133_0229ba10(void *);
extern void *data_021f43ec;

int func_ov133_0229bb78(char *self, int a1, int a2)
{
    // DECLS
    char frame[0x8];
    // ENDDECLS
    *(u8 *) (frame) = *(u8 *) ((char *) &data_021f43ec);
    *(u8 *) (frame) = a1;
    func_ov002_0220b9b8(self + 0x1394, frame, a2, 0x0);
    func_ov002_02208098(self, 0xb);
    return func_ov133_0229ba10(self);
}
