/* func_0204a200 @ 0x0204a200, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern void func_0204f564(unsigned int, unsigned short *, unsigned int, unsigned int, unsigned int, unsigned int, int);
extern void func_0204f3a4(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern void func_0204f340(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

void func_0204a200(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int a4, unsigned int a5,
                   unsigned short d, unsigned int flag)
{
    volatile unsigned short tmp;
    unsigned int v5;
    unsigned int v4;

    tmp = 0xFFF1;
    tmp = d;
    v5 = a5;
    v4 = a4;
    func_0204f564(p1, (unsigned short *) &tmp, p2, p3, v4, v5, 0);
    if (flag != 0) {
        func_0204f3a4(p1, p2, p3, v4, v5);
    } else {
        func_0204f340(p1, p2, p3, v4, v5);
    }
}
