/* func_ov003_0222f958 @ 0x0222f958, 0xc8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov003_02230f60(void *self);

void func_ov003_0222f958(int a, char *self)
{
    u8 s;
    short n;
    short *p;

    if (*(int *) (self + 0x170) == 0) {
        return;
    }
    switch (*(signed char *) (self + 0x24d)) {
        case 0x1e:
            s = *(u8 *) (self + 0x251);
            if (s == 4 || s == 5 || s == 0x11) {
                n = *(short *) (self + 0x232);
                if (n > 5) {
                    *(short *) (self + 0x232) = n - 1;
                } else {
                    func_ov003_02230f60(self);
                }
            }
            break;
        case 0x31:
            switch (*(u8 *) (self + 0x251)) {
                case 4:
                case 5:
                case 7:
                case 0x11:
                    n = *(short *) (self + 0x232);
                    if (n > 0) {
                        *(short *) (self + 0x232) = n - 1;
                    } else {
                        func_ov003_02230f60(self);
                    }
                    break;
            }
            break;
        case 0x36:
        case 0x37:
            p = (short *) (self + 0x236);
            n = *p;
            if (n > 0 && n <= 0x12c) {
                if (n > 0x1f) {
                    *p = n - 1;
                } else {
                    func_ov003_02230f60(self);
                }
            }
            break;
    }
}
