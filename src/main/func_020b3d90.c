/* func_020b3d90 @ 0x020b3d90, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b3f08(int *p);
extern int func_020b3f2c(int *p);
extern int func_020b3ed4(int *p);

int func_020b3d90(int *p)
{
    int a, b;
    a = func_020b3f08(p);
    b = func_020b3f2c(p);
    return p[a + (b + func_020b3ed4(p)) + 1];
}
