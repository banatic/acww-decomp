/* func_020b12e0 @ 0x020b12e0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b1530(int param);
extern void func_020b15b8(int param, int *out0, int *out1);
extern void func_020ba3bc(void *param, int x, int y);

void func_020b12e0(void *a, int b)
{
    int local0, local1;
    func_020b15b8(func_020b1530(b) + 0x2a, &local0, &local1);
    local0 -= 0x80;
    local1 -= 0x60;
    func_020ba3bc(a, local0, local1);
}
