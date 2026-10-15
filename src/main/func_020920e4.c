/* func_020920e4 @ 0x020920e4, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int FX_MulFunc(int, int);
extern void func_02094260(unsigned int *object, unsigned int value);

struct Glob {
    char pad_00[0x10];
    short unk_10;
};

extern struct Glob data_021d5658;

void func_020920e4(void *arg)
{
    int sum = FX_MulFunc(0x2000, data_021d5658.unk_10) + 0x99a;
    func_02094260((unsigned int *) arg, sum);
}
