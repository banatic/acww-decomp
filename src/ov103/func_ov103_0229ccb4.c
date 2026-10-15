/* func_ov103_0229ccb4 @ 0x0229ccb4, 0x34 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov103_0229cdfc(int arg0, unsigned int arg1);
extern int func_ov103_0229cde8(int a, int b);
extern int func_ov094_0229b384(int a, int b);

int func_ov103_0229ccb4(int a, int b)
{
    if (func_ov103_0229cdfc(a, b) != 0) {
        int r = func_ov103_0229cde8(a, b);
        return func_ov094_0229b384(a + 0xb2c, r);
    } else {
        return 0;
    }
}
