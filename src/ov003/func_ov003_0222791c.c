/* func_ov003_0222791c @ 0x0222791c, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

int func_020644cc(int n);
int func_ov003_0222793c(int a, int b);
int func_ov003_0222791c(int a, int b)
{
    int v = func_ov003_0222793c(a, b);
    if (func_020644cc(2) == 0) {
        v *= -1;
    }
    return v;
}
