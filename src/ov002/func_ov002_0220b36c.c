/* func_ov002_0220b36c @ 0x0220b36c, 0xe bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

void func_ov002_0220b36c(char *p, int a, u8 b, u8 c)
{
    *(int *) (p + 0x70) = a;
    *(u8 *) (p + 0x74) = b;
    *(u8 *) (p + 0x76) = c;
}
