/* func_0204a25c @ 0x0204a25c, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204f538(unsigned int, unsigned short *, unsigned int, unsigned int, int);
extern void func_0204f380(unsigned int, unsigned int, unsigned int);
extern int func_0204f31c(unsigned int, unsigned int, unsigned int);

void func_0204a25c(unsigned int a, unsigned int b, unsigned int c, unsigned short d, unsigned int e)
{
    volatile unsigned short tmp;
    tmp = 0xFFF1;
    tmp = d;
    func_0204f538(a, (unsigned short *) &tmp, b, c, 0);
    if (e != 0) {
        func_0204f380(a, b, c);
    } else {
        func_0204f31c(a, b, c);
    }
}
