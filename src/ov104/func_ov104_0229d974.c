/* func_ov104_0229d974 @ 0x0229d974, 0x48 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov104_0229d7bc(unsigned char *a, int b);
extern int func_ov104_0229d8f8(unsigned char *a, int b);
extern void func_02066830(unsigned char *ptr, int val);
extern void func_ov104_0229d938(unsigned char *a, int byte, unsigned char *ptr);
extern void func_ov104_0229d484(unsigned char *a, int b);

int func_ov104_0229d974(unsigned char *a, int b)
{
    if (func_ov104_0229d7bc(a, b) == 0) {
        func_02066830(a + 0x1c0, func_ov104_0229d8f8(a, b));
        func_ov104_0229d938(a, a[0xb7], a + 0x1c0);
    }
    func_ov104_0229d484(a, b);
    return 1;
}
