/* func_0207557c @ 0x0207557c, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(const void *src, void *dest, int size);
extern int func_0209847c(int arg);
extern int func_020962a4(int a, int b);

int func_0207557c(char *p0, int p1, int p2)
{
    int local;
    int p2_plus_3;
    int r;

    MI_CpuCopy8(p0, &local, 4);
    p2_plus_3 = p2 + 3;
    r = func_0209847c(p2_plus_3);
    MI_CpuCopy8(p0 + 4, (void *) (r + local), p1 - 4);
    return func_020962a4(p2, p2_plus_3);
}
