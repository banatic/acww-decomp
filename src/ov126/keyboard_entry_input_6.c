/* keyboard_entry_input_6: 2 functions, module ov126
 * mwccarm 1.2/base -O4,s
 * func_ov126_022a0740 @ 0x022a0740, 0x28 bytes, Thumb
 * func_ov126_022a0728 @ 0x022a0728, 0x18 bytes, Thumb
 */

struct UnkStruct_022a0740 {
    char pad_00[0xa9];
    unsigned char b1;
    unsigned char b2;
};

struct UnkStruct_022a0728 {
    char pad_00[0xa9];
    unsigned char b1;
    unsigned char b2;
};

extern int func_ov126_0229f7c8(struct UnkStruct_022a0740 *p, int x);
extern void func_ov126_0229f7a8(void *p, int arg);

int func_ov126_022a0740(struct UnkStruct_022a0740 *p)
{
    if ((func_ov126_0229f7c8(p, 4) == 0) || (p->b1 == p->b2)) {
        return 0;
    }
    return 1;
}

void func_ov126_022a0728(struct UnkStruct_022a0728 *p)
{
    p->b1 = 0;
    p->b2 = 0;
    func_ov126_0229f7a8(p, 4);
}
