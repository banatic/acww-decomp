/* func_ov094_0229b738 @ 0x0229b738, 0x44 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099734(int);
extern int func_02098e44(int, int);
extern void func_ov094_0229b3f0(int, int, int, int, int);

void func_ov094_0229b738(int a, int b, int c)
{
    int v1;
    int v2;
    int base;
    int i;
    int j;

    v1 = func_020984e8();
    v2 = func_02099734(v1);
    base = func_02098e44(v2, 0);

    i = 0;
    for (j = 0; j < 10; j++) {
        func_ov094_0229b3f0(a, base, i, b, c);
        base += 0x100;
        i++;
    }
}
