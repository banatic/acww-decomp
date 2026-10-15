/* func_ov068_02274490 @ 0x02274490, 0x20 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02274490 {
    char pad_00[0x730];
    int value;
};

struct Main {
    char pad_00[0xb4];
    struct UnkStruct_02274490 *sub;
};

extern void func_ov068_0227440c(struct Main *param, int arg2);

void func_ov068_02274490(struct Main *param, int arg2)
{
    if (param->sub->value == 7) {
        func_ov068_0227440c(param, arg2);
    }
}
