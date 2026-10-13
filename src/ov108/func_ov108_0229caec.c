/* func_ov108_0229caec @ 0x0229caec, 0x44 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov108_0229cd70(char *a, int b);
extern int func_ov108_0229cd5c(char *a, int b);
extern void func_ov094_0229b950(char *p, int x);
extern void func_ov094_0229ab5c(char *p);
extern void func_ov108_0229cb30(char *a);

void func_ov108_0229caec(char *a, int b)
{
    if (func_ov108_0229cd70(a, b)) {
        func_ov094_0229b950(a + 0xd50, func_ov108_0229cd5c(a, b));
        func_ov094_0229ab5c(a + 0x2f0);
    } else {
        func_ov108_0229cb30(a);
    }
}
