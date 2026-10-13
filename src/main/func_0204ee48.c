/* func_0204ee48 @ 0x0204ee48, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f800(int *a, int *b, int c, int d, int e, int f);
extern void func_0204ee7c(int a, int b, int c);

void func_0204ee48(int a, int b, int c, int d, int e)
{
    int out1 = 0;
    int out2 = 0;

    func_0204f800(&out1, &out2, b, c, d, e);
    func_0204ee7c(a, out1, out2);
}
