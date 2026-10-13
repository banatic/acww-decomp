/* func_ov121_0229abc8 @ 0x0229abc8, 0x38 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(unsigned char *a, int i, int j);
extern int func_020996b8(int a);
extern int func_02072ba4(int a);
extern void func_02072b74(int a, int i, int j);

void func_ov121_0229abc8(unsigned char *a, int i, int j)
{
    unsigned char *p;
    unsigned char t;
    if (i != j) {
        func_02072b74(func_02072ba4(func_020996b8(func_020984e8(a, i, j))), i, j);
        p = a + 0x118c;
        t = p[i];
        p[i] = p[j];
        p[j] = t;
    }
}
