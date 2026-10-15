/* func_0209e314 @ 0x0209e314, 0x3a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209de88(int year, int month, int day);
extern void func_0209e140(unsigned char *, unsigned int);
extern void MI_CpuCopy8(const void *, void *, unsigned int);

void func_0209e314(unsigned char *a, unsigned char *b)
{
    unsigned int ret;
    if (b == 0) {
        return;
    }
    ret = func_0209de88(a[5], a[4], a[3]);
    if (b != a) {
        MI_CpuCopy8(a, b, 8);
    }
    func_0209e140(b, ret);
    b[2] = 0;
    b[1] = 0;
    b[0] = 0;
}
