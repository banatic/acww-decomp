/* func_ov108_0229cb88 @ 0x0229cb88, 0x34 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov108_0229cd70(char *a, int b);
extern int func_ov108_0229cd5c(char *a, int b);
extern int func_ov094_0229b788(char *p, int n);

int func_ov108_0229cb88(char *a, int b)
{
    if (func_ov108_0229cd70(a, b)) {
        return func_ov094_0229b788(a + 0xd50, func_ov108_0229cd5c(a, b));
    }
    return 0;
}
