/* func_0209c470 @ 0x0209c470, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209c42c(void *a, unsigned char b, unsigned char val);
extern unsigned char func_0209c410(void *a, unsigned char b);

void func_0209c470(void *a, unsigned char b)
{
    int i;
    unsigned char val;

    func_0209c42c(a, b, 0);
    for (i = 0; i < 8; i++) {
        val = func_0209c410(a, (unsigned char) i);
        func_0209c42c(a, (unsigned char) i, val >> 1);
    }
}
