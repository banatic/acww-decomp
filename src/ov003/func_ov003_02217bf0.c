/* func_ov003_02217bf0 @ 0x02217bf0, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02077978(unsigned char *a, int c, int d);
extern int func_020778f8(unsigned char *a);

void func_ov003_02217bf0(unsigned char *a, unsigned char *b, int c, int d, unsigned short *e)
{
    *b = a[7];
    func_02077978(a, c, d);
    *e = func_020778f8(a + 5);
}
