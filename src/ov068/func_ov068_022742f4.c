/* func_ov068_022742f4 @ 0x022742f4, 0x20 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov068_02274238(void *self, int b);

struct inner_022743ec {
    char pad_00[0x730];
    int value;
};

struct outer_022743ec {
    char pad_00[0xb4];
    struct inner_022743ec *inner;
};

void func_ov068_022742f4(struct outer_022743ec *a, int b)
{
    if (a->inner->value == 7) {
        func_ov068_02274238(a, b);
    }
}
