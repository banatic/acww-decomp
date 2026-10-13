/* func_ov068_022743ec @ 0x022743ec, 0x20 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov068_02274358(void *a, void *b);

struct inner_022743ec {
    char pad_00[0x730];
    int value;
};

struct outer_022743ec {
    char pad_00[0xb4];
    struct inner_022743ec *inner;
};

void func_ov068_022743ec(struct outer_022743ec *a, void *b)
{
    if (a->inner->value == 7) {
        func_ov068_02274358(a, b);
    }
}
