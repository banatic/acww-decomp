/* func_020261f8 @ 0x020261f8, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0209b8bc(int);
extern unsigned int func_0207ff00(int);
extern unsigned int func_0209b7ac(unsigned int, unsigned int);
extern void func_0209b8a4(int, unsigned int);
extern void func_02078624(int, unsigned int);
extern void func_0209b750(unsigned short *, unsigned int, int);

void func_020261f8(unsigned short *p1, int p2, int p3)
{
    unsigned int r4;

    r4 = func_0209b8bc(p2);
    if (r4 == 0x18) {
        r4 = (unsigned char) func_0209b7ac(func_0207ff00(p3), 0xA);
        func_0209b8a4(p2, r4);
        func_02078624(p3, r4);
    }
    if (r4 < 0x18) {
        func_0209b750(p1, r4, 0);
    } else {
        *p1 = 0xFFF1;
    }
}
