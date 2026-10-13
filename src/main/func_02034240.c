/* func_02034240 @ 0x02034240, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02033cec(int, int *, int, int);

int func_02034240(int a0, int a1, int a2, int a3, int a4)
{
    int local[3];
    local[0] = (a1 << 13) + 0x1000;
    local[1] = 0;
    local[2] = (a2 << 13) + 0x1000;
    func_02033cec(a0, local, a3, a4);
    return a0;
}
