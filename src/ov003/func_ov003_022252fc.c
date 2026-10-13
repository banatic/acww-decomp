/* func_ov003_022252fc @ 0x022252fc, 0x60 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int w[12];
} Big;
void func_ov003_022251a4(void *self, void *o, Big s);

void *func_ov003_022252fc(char *self, u16 *k, Big s)
{
    int i = 0;
    void *o;
    if (*k == 0xfd) {
        i = 1;
    }
    o = self + 0x4708 + 0x9c * i;
    func_ov003_022251a4(self, o, s);
    return o;
}
