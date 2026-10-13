/* func_ov126_0229f90c @ 0x0229f90c, 0x24 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov126_0229fc54(void);
extern int func_02077c34(void);
extern void func_02051c08(int, int, int);

void func_ov126_0229f90c(int *param)
{
    int *r4;
    int r0;
    int r1;
    int r2;

    r4 = param;
    func_ov126_0229fc54();
    r0 = func_02077c34();
    r1 = r0;
    r0 = (int) r4 + 0x4248;
    r2 = 6;
    func_02051c08(r0, r1, r2);
}
