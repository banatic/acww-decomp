/* func_ov003_022253a8 @ 0x022253a8, 0x5c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int w[12];
} Big;
void func_ov003_022251a4(void *self, void *o, Big s);

void *func_ov003_022253a8(char *self, u16 *k, Big s)
{
    void *o = *(void **) (self + ((*k - 0xe3) % 5) * 4 + 0x46f4);
    func_ov003_022251a4(self, o, s);
    return o;
}
