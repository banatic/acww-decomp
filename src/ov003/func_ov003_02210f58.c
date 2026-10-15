/* func_ov003_02210f58 @ 0x02210f58, 0x48 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

unsigned int func_0200e92c(void *);
void func_0200e90c(void *, int, int, short);
int func_0200e894(int, void *);
int func_0200e91c(void *);

int func_ov003_02210f58(int a, int *b, int c, int d, short e)
{
    u8 msg[0x20];
    u8 *out;
    int ret;

    func_0200e92c(msg);
    out = &msg[0xc];
    func_0200e90c(msg, 0x60, d, e);
    out[0] = (u8) b[0];
    out[1] = (u8) b[1];
    out[2] = (u8) c;
    ret = func_0200e894(a, msg);
    func_0200e91c(msg);
    return ret;
}
