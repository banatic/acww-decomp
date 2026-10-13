/* func_020108cc @ 0x020108cc, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u8 data_020e54a8;
extern int func_0200f290(void *a, int z);
extern void func_020110c4(u16 *p, void *a);
extern void func_0201079c(void *a, u16 *p, int b, int c);

void func_020108cc(void *a, int b, int c)
{
    u16 v[3];
    int flag;

    v[0] = 0xfff1;
    // The ternary and the explicit flag == 0 test produce the 1/0 pair.
    flag = data_020e54a8 ? 0 : 1;
    // The reset arm comes first in the original.
    if (flag == 0 || func_0200f290(a, 0) == 0) {
        v[0] = 0xfff1;
    } else {
        func_020110c4(&v[1], a);
        v[0] = v[1];
    }
    v[2] = v[0];
    func_0201079c(a, &v[2], b, c);
}
