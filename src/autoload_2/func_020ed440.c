/* func_020ed440 @ 0x020ed440, 0x8c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern void MI_CpuFill8(void *, int, int);
extern char *data_021fbf3c;
extern void (*data_021fbf30)(int);

void func_020ed440(int x)
{
    MI_CpuFill8(data_021fbf3c + 12 * x, 0, 12);
    {
        int off = 35 * x;
        MI_CpuFill8(data_021fbf3c + 0x180 + off, 0, 35);
        *(char *) (data_021fbf3c + off + 0x1a0) = 0;
    }
    if (data_021fbf30 == 0) {
        return;
    }
    data_021fbf30(x);
}
