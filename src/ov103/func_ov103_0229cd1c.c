/* func_ov103_0229cd1c @ 0x0229cd1c, 0x30 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov103_0229cdfc(int arg0, unsigned int arg1);
extern int func_ov103_0229cde8(int, int);
extern void func_ov094_0229b8b4(int, int, int);

void func_ov103_0229cd1c(int a, int b, int c)
{
    int r5 = a;
    int r4 = b;
    int r6 = c;

    if (func_ov103_0229cdfc(a, b) != 0) {
        int r0 = func_ov103_0229cde8(r5, r4);
        func_ov094_0229b8b4(r5 + 0xb2c, r0, r6);
    }
}
