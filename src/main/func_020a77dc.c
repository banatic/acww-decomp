/* func_020a77dc @ 0x020a77dc, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a7890(int a, int b, int c, int d, int e, int f);

void func_020a77dc(int a, int b, int c, int d, int e, int f)
{
    int local[2];
    local[0] = e;
    local[1] = f;
    func_020a7890(a, b, c, d, local[0], local[1]);
}
