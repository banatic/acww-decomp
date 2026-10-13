/* func_0209a14c @ 0x0209a14c, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_0209a19c(unsigned short);
extern void func_02061e2c(unsigned short *, unsigned short *);
extern void func_0209a088(unsigned short *, int, unsigned int);

void func_0209a14c(unsigned short *a, unsigned int b)
{
    unsigned short x, y;
    int flag = 0;

    x = 0xfff1;
    if (*a == 0x156b) {
        x = func_0209a19c(0x156b);
        flag = 1;
    } else {
        func_02061e2c(&y, a);
        x = y;
    }
    func_0209a088(&x, flag, b);
}
