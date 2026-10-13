/* func_020acbc8 @ 0x020acbc8, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020310c8(int);
extern void func_020acc0c(int *, int, int, int);

void func_020acbc8(int *a, int b)
{
    int local[3];
    local[0] = a[0];
    local[1] = a[1];
    local[2] = a[2];
    local[1] -= func_020310c8(0) + 0x800;
    func_020acc0c(local, b, 0xe00, 0x1000);
}
