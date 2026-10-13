/* func_ov003_0221a4f0 @ 0x0221a4f0, 0x48 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f818(int *a, int *b, int c);
extern int func_0204f538(int a, unsigned short *b, int c, int d, int e);

extern int data_021c80bc;

int func_ov003_0221a4f0(int param)
{
    unsigned short s;
    int a, b;
    int v;

    v = data_021c80bc;
    if (v != 0) {
        func_0204f818(&a, &b, param);
        s = 0xfff1;
        if (func_0204f538(v, &s, a, b, 0) != 0) {
            return 1;
        }
    }
    return 0;
}
