/* func_ov068_0227580c @ 0x0227580c, 0x40 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201af28(char *addr, int a, int b, int c, int d);

int func_ov068_0227580c(char *p)
{
    *(unsigned short *) (p + 0x0a52) = 5;
    func_0201af28(p + 0x350, 1, 0x148, 0x25, 0x25);
    *(unsigned short *) (p + 0x0a5e) = 0x258;
    return 1;
}
