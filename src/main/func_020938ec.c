/* func_020938ec @ 0x020938ec, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02094c38(void *a, int b, int c);

struct UnkStruct_020938ec {
    char pad_00[0x54];
    unsigned int value;
};

struct UnkStruct_020938ec_2 {
    char pad_00[0xc];
    struct UnkStruct_020938ec *inner;
};

void func_020938ec(struct UnkStruct_020938ec_2 *arg)
{
    int zero = 0;
    func_02094c38(arg, zero, zero);
    arg->inner->value = 0x800;
}
