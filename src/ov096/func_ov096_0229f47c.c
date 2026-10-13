/* func_ov096_0229f47c @ 0x0229f47c, 0x30 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229f820(void);
extern int func_ov096_0229f548(int, int);
extern void func_ov094_0229b8b4(int, int, int);

void func_ov096_0229f47c(int a, int b, int c)
{
    int r5 = a;
    int r4 = b;
    int r6 = c;
    if (func_ov096_0229f820()) {
        int r0 = func_ov096_0229f548(r5, r4);
        func_ov094_0229b8b4(r5 + 0xdb8, r0, r6);
    }
}
