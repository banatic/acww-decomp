/* func_02093930 @ 0x02093930, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct func_02093930_inner {
    char pad_00[0x54];
    unsigned int value;
};

struct func_02093930_outer {
    char pad_00[0xC];
    struct func_02093930_inner *inner;
};

extern void func_02094c38(struct func_02093930_outer *a, int b, int c);

void func_02093930(struct func_02093930_outer *a)
{
    int zero = 0;
    func_02094c38(a, zero, zero);
    a->inner->value = 0x666;
}
