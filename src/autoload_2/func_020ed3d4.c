/* func_020ed3d4 @ 0x020ed3d4, 0x6c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int *data_021fbf40;
extern void func_020ed440(void);
extern void func_020ed540(void);
extern void func_020ed4cc(void);
extern void func_ov065_0227982c(int *, int);
extern void func_ov065_02277edc(int, void (*)(void), int, void (*)(void), int, void (*)(void), int);

void func_020ed3d4(int a, int b, int c)
{
    if (a != 0) {
        return;
    }
    func_ov065_0227982c(data_021fbf40, 0x20);
    func_ov065_02277edc(0, func_020ed540, c, func_020ed4cc, c, func_020ed440, c);
}
