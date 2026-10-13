/* func_020920e4 @ 0x020920e4, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int FX_MulFunc(int, short, void *);
extern int func_02094260(int, int);

struct Glob {
    char pad_00[0x10];
    short unk_10;
};

extern struct Glob data_021d5658;

int func_020920e4(int arg)
{
    int sum;
    sum = FX_MulFunc(0x2000, data_021d5658.unk_10, &data_021d5658) + 0x99A;
    return func_02094260(arg, sum);
}
