/* func_ov120_0229b784 @ 0x0229b784, 0x48 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *p);
extern int func_ov120_0229a4bc(void *p);
extern void func_ov120_0229abec(void *p, int a);
extern void func_ov120_0229a6f0(void *p);

void func_ov120_0229b784(void *p)
{
    if (func_0208e484((char *) p + 0x6bc) != 0) {
        int v = func_ov120_0229a4bc(p);
        if (v == 1) {
            return;
        }
        if (v == 2) {
            func_ov120_0229abec(p, 0);
            *((unsigned char *) p + 0xa3) = 0xff;
            func_ov120_0229a6f0(p);
            return;
        }
        func_ov120_0229a6f0(p);
    }
}
