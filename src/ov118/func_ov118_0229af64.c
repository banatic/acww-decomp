/* func_ov118_0229af64 @ 0x0229af64, 0x70 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov118_0229a450(void *p, int n);
extern void func_0206fdd4(char *dst, int a, int b, int c, int d, int e);

void func_ov118_0229af64(void *p, int n)
{
    func_ov118_0229a450(p, 0x80);
    if (n == 14) {
        func_0206fdd4((char *) p + 0x1724, 0x13, 0, 0x1c, 25, 4);
    } else if (n == 13) {
        func_0206fdd4((char *) p + 0x1724, 0x13, 0, 0x1c, ((unsigned char *) p)[0xb0] * 2 - 1, 3);
    } else {
        func_0206fdd4((char *) p + 0x1724, 0x13, n * 2, 0x1c, n * 2 + 1, 3);
    }
}
