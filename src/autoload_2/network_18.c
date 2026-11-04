/* network_18: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020ed440 @ 0x020ed440, 0x8c bytes, ARM
 * func_020ed3d4 @ 0x020ed3d4, 0x6c bytes, ARM
 */

extern void MI_CpuFill8(void *, int, int);
extern char *data_021fbf3c;
extern void (*data_021fbf30)(int);
extern int *data_021fbf40;
extern void func_020ed540(void *result, int changed, void *user_data);
extern void func_020ed4cc(int index, int status, void *profile, void *user_data);
extern int func_ov065_0227982c(int *, int);
extern int func_ov065_02277edc(int, void (*)(void *, int, void *), int, void (*)(int, int, void *, void *), int,
                               void (*)(int, int, void *), int);

void func_020ed440(int x, int reason, void *user_data)
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

void func_020ed3d4(int a, int b, int c)
{
    if (a != 0) {
        return;
    }
    func_ov065_0227982c(data_021fbf40, 0x20);
    func_ov065_02277edc(0, func_020ed540, c, func_020ed4cc, c, func_020ed440, c);
}
