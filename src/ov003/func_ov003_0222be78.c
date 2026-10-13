/* func_ov003_0222be78 @ 0x0222be78, 0x1e bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

void func_ov003_0222bec4(void *out, int a, u16 ang);
void func_ov003_0222be98(void *out, int a, u16 ang);

void func_ov003_0222be78(char *self, int a, u16 ang)
{
    func_ov003_0222bec4(self, a, ang);
    func_ov003_0222be98(self + 8, a, ang);
}
