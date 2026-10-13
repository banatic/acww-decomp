/* func_ov004_02229718 @ 0x02229718, 0x22 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02077978(char *p, int b, int c);
extern short func_020778f8(char *p);
void func_ov004_02229718(char *p, int b, int c, short *out, u8 *out2)
{
    func_02077978(p, b, c);
    *out = func_020778f8(p + 5);
    *out2 = *(u8 *) (p + 7);
}
