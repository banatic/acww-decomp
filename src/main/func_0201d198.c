/* func_0201d198 @ 0x0201d198, 0xfc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int a, b;
} Entry;

extern Entry data_021c2114[17];
extern Entry data_0213dd98;
extern Entry data_020d8fd8;
extern Entry data_020d8fb0;
extern Entry data_020d8ee0;
extern Entry data_020d8f30;
extern Entry data_020d9210;
extern Entry data_020d91a0;
extern Entry data_020d92c0;
extern unsigned int data_021c1d04;

typedef int (*Fn)(void *);

int func_0201d198(void *self, unsigned int idx)
{
    if ((data_021c1d04 & 1) == 0) {
        Entry def = data_0213dd98;
        data_021c2114[0] = def;
        data_021c2114[1] = data_020d8fd8;
        data_021c2114[2] = def;
        data_021c2114[3] = def;
        data_021c2114[4] = def;
        data_021c2114[5] = def;
        data_021c2114[6] = def;
        data_021c2114[7] = data_020d8fb0;
        data_021c2114[8] = def;
        data_021c2114[9] = def;
        data_021c2114[10] = def;
        data_021c2114[11] = def;
        data_021c2114[12] = data_020d8ee0;
        data_021c2114[13] = data_020d8f30;
        data_021c2114[14] = data_020d9210;
        data_021c2114[15] = data_020d91a0;
        data_021c2114[16] = data_020d92c0;
        data_021c1d04 |= 1;
    }

    if (idx < 17) {
        Entry *e = &data_021c2114[idx];
        if (e->a != 0) {
            char *base = (char *) self + ((int) e->b >> 1);
            char *vtable;
            Fn func;
            if (e->b & 1) {
                vtable = *(char **) base;
                func = *(Fn *) (vtable + e->a);
            } else {
                func = (Fn) (*(volatile unsigned int *) &e->a);
            }
            return func(base);
        }
    }
    return 0;
}
