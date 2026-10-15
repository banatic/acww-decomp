/* func_0207718c @ 0x0207718c, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02077afc(int a, int b);
extern void func_020738e0(int a, int b);
extern void func_02077598(int a);
extern void MI_CpuFill8(int a, int b, int c);
extern int data_020ccf94;

void func_0207718c(void)
{
    int r4;
    int i;

    r4 = func_02077afc(0x6a0, 4);
    func_020738e0(data_020ccf94, r4);
    if (r4 != 0) {
        MI_CpuFill8(r4, 0, 0x6a0);
    }
    for (i = 0; i < 0x46; i++) {
        func_02077598(i);
    }
}
