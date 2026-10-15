/* func_020449ac @ 0x020449ac, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f794(void *dst, unsigned int a, unsigned int b);
extern int func_02090c2c(int a, void *b, int c, void *d);

extern unsigned char data_020e25d4[];

void func_020449ac(unsigned int *src)
{
    unsigned int a, b;
    unsigned int local[3];

    a = src[0];
    b = src[1];
    func_0204f794(local, a, b);
    func_02090c2c(0x94, local, 0, (void *) data_020e25d4);
}
