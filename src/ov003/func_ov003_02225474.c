/* func_ov003_02225474 @ 0x02225474, 0xc4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int w[12];
} Big;

extern void func_ov003_022251a4(void *self, void *p, Big b);

void *func_ov003_02225474(char *self, u16 *key, Big b)
{
    void *p;

    switch (*key) {
        case 0x1a:
            p = self + 0x2df0;
            break;
        case 0x1b:
            p = self + 0x2f28;
            break;
        case 0x1c:
            break;
        case 0x1d:
            p = *(void **) (self + 0x3060);
            break;
        case 0x1e:
            p = *(void **) (self + 0x3064);
            break;
        case 0x88:
        case 0xa4:
            p = self + 0x2e8c;
            break;
        case 0x89:
            p = self + 0x2fc4;
            break;
    }
    func_ov003_022251a4(self, p, b);
    return p;
}
