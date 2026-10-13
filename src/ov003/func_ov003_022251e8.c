/* func_ov003_022251e8 @ 0x022251e8, 0x58 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int w[12];
} Big;
void func_ov003_022251a4(void *self, void *o, Big s);

void *func_ov003_022251e8(char *self, u16 *k, Big s)
{
    void *o = self + 0x3068 + 0x9c * (*k - 0xa7);
    func_ov003_022251a4(self, o, s);
    return o;
}
