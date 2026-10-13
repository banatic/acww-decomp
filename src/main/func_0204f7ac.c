/* func_0204f7ac @ 0x0204f7ac, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f800(int *out1, int *out2, int in1, int in2);
extern int func_0204f794(int a, int b, int c);

int func_0204f7ac(int a, int b, int c, int d, int e)
{
    struct {
        int d;
        int e;
        int x;
        int y;
    } local;

    local.x = 0;
    local.y = 0;
    local.d = d;
    local.e = e;
    func_0204f800(&local.x, &local.y, b, c);
    return func_0204f794(a, local.x, local.y);
}
