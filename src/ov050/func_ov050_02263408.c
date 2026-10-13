/* func_ov050_02263408 @ 0x02263408, 0xac bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int);
extern void func_0209a000(void *, int);
extern void func_020154b4(void *, void *, int, int, int);

void func_ov050_02263408(void *arg)
{
    unsigned short a, b, c, d, e, f;
    int i;

    a = (unsigned short) (func_020644cc(3) + 0x14fe);
    func_0209a000(&a, 0);

    b = (unsigned short) (func_020644cc(3) + 0x1504);
    func_0209a000(&b, 0);

    c = (unsigned short) (func_020644cc(3) + 0x150a);
    func_0209a000(&c, 0);

    d = (unsigned short) (func_020644cc(3) + 0x1510);
    func_0209a000(&d, 0);

    for (i = 0; i < 3; i++) {
        e = 0x151d;
        func_0209a000(&e, 0);
    }

    f = 0x151d;
    func_020154b4(arg, &f, 0, 5, 0);
}
