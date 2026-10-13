/* func_ov003_0222b8bc @ 0x0222b8bc, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

void func_ov003_022277fc(void *p, int k);
void func_ov003_0222803c(void *p, int k);
int func_ov003_0222793c(int a, int b);

void func_ov003_0222b8bc(char *self)
{
    func_ov003_022277fc(self, 0xa);
    func_ov003_0222803c(self + 0x120, 0x40);
    if (func_ov003_0222793c(0, 0x64) == 1 || *(int *) (self + 0x13c) > 0x64) {
        *(u8 *) (self + 0x200) = 0;
    }
}
