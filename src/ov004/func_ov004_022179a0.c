/* func_ov004_022179a0 @ 0x022179a0, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef void (*Fn)(void *self, int a, int b);

void func_ov004_022179a0(void *self, int k)
{
    switch (k) {
        case 0:
        case 1:
            if (*(int *) ((char *) self + 0x858) == 1) {
                (*(Fn **) self)[28](self, 2, 0xff);
            } else {
                (*(Fn **) self)[28](self, 7, 0xff);
            }
            break;
        case 8:
            (*(Fn **) self)[28](self, 1, 0xff);
            break;
    }
}
