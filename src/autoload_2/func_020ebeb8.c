/* func_020ebeb8 @ 0x020ebeb8, 0xb8 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int func_020ec920(void);
extern int func_020ebf70(void);
extern int func_020ed73c(int a, int b, int c, int d);
extern int func_020ed9f4(void);
extern void func_020ed8f4(void);

int func_020ebeb8(int a, int b, int c, int d, int e, int f, unsigned short g, int h, int i, int j, unsigned short k, int l)
{
    int v1, v2, v3;
    if (func_020ec920() != 0 && func_020ebf70() != 0) {
        v1 = func_020ed73c(a, b, c, d);
        v2 = func_020ed73c(e, f, g, h);
        v3 = func_020ed73c(i, j, k, l);
        if (v1 != 0 || v2 != 0 || v3 != 0) {
            if (func_020ed9f4() != 0) {
                return 1;
            }
            func_020ed8f4();
        }
    }
    return 0;
}
