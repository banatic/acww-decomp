/* func_ov108_0229cc90 @ 0x0229cc90, 0x30 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov108_0229cd70(void);
extern int func_ov108_0229cd5c(int, int);
extern void func_ov094_0229b8b4(int, int, int);

void func_ov108_0229cc90(int a, int b, int c)
{
    int r5 = a;
    int r4 = b;
    int r6 = c;

    if (func_ov108_0229cd70() != 0) {
        int r0 = func_ov108_0229cd5c(r5, r4);
        func_ov094_0229b8b4(r5 + 0xd50, r0, r6);
    }
}
