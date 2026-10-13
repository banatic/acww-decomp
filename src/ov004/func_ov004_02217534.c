/* func_ov004_02217534 @ 0x02217534, 0x4c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0220d280(void *p, int a, int b);
extern void func_ov004_02210054(void *self, int a, int b, int c);
extern void func_ov004_022101e4(void *self, int a, int b, int c, int d);

int func_ov004_02217534(void *self)
{
    func_ov004_0220d280((char *) self + 0x740, 1, 0);
    if (*(int *) ((char *) self + 0x780) == 0xf) {
        func_ov004_02210054(self, 1, 1, 0x1000);
    } else {
        func_ov004_022101e4(self, 0, 3, 0x1000, 0);
    }
    return 1;
}
