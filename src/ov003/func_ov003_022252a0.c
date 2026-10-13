/* func_ov003_022252a0 @ 0x022252a0, 0x5c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int w[12];
} Big;
void func_ov003_022251a4(void *self, void *o, Big s);

void func_ov003_022252a0(char *self, u16 *k, Big s)
{
    int i = 0;
    if (*k == 0xfe) {
        i = 1;
    }
    func_ov003_022251a4(self, self + 0x4840 + 0x9c * i, s);
}
