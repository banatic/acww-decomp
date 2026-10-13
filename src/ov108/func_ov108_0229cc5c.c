/* func_ov108_0229cc5c @ 0x0229cc5c, 0x34 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov108_0229cd70(int a, int b);
extern int func_ov108_0229cd5c(int a, int b);
extern int func_ov094_0229b8d8(int a, int b);

int func_ov108_0229cc5c(int a, int b)
{
    if (func_ov108_0229cd70(a, b)) {
        return func_ov094_0229b8d8(a + 0xd50, func_ov108_0229cd5c(a, b));
    }
    return 0;
}
