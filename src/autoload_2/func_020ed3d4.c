/* func_020ed3d4 @ 0x020ed3d4, 0x6c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int *data_021fbf40;
extern void func_020ed440(int index, int reason, void *user_data);
extern void func_020ed540(void *result, int changed, void *user_data);
extern void func_020ed4cc(int index, int status, void *profile, void *user_data);
extern int func_ov065_0227982c(int *, int);
extern int func_ov065_02277edc(int, void (*)(void *, int, void *), int, void (*)(int, int, void *, void *), int,
                               void (*)(int, int, void *), int);

void func_020ed3d4(int a, int b, int c)
{
    if (a != 0) {
        return;
    }
    func_ov065_0227982c(data_021fbf40, 0x20);
    func_ov065_02277edc(0, func_020ed540, c, func_020ed4cc, c, func_020ed440, c);
}
