/* func_020f6564 @ 0x020f6564, 0x1c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int func_0210e1d0(int a, int b);

struct Global_021fd1bc {
    char pad_00[0x28];
    int unk_28;
};

extern struct Global_021fd1bc data_021fd1bc;

int func_020f6564(int a, int b)
{
    return func_0210e1d0(b, data_021fd1bc.unk_28);
}
