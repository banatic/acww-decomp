/* func_ov068_022738d8 @ 0x022738d8, 0x10 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov068_022738e8(void);

struct UnkStruct_022738d8 {
    char pad_00[0x1c];
    void (*func)(void);
    char pad_20[0x70];
    char flag;
};

void func_ov068_022738d8(struct UnkStruct_022738d8 *self)
{
    self->func = func_ov068_022738e8;
    self->flag = 2;
}
