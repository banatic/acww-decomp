/* func_ov133_0229ba84 @ 0x0229ba84, 0x58 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern const int data_ov133_0229c7b4[];
extern int func_ov002_0220a768(char *p, int i);

int func_ov133_0229ba84(char *self)
{
    u8 k = *(u8 *) (self + 0x9c);

    if (k <= 0xb) {
        return data_ov133_0229c7b4[k];
    }
    switch (k) {
        case 0xc:
            return (*(u8 *) (self + 0x9f) << 4) + 0x20;
        case 0xd:
            return func_ov002_0220a768(self + 0x180, 6);
        case 0xe:
            return func_ov002_0220a768(self + 0x180, 7);
    }
    return 0x80;
}
