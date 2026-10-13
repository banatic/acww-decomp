/* func_0208f6a0 @ 0x0208f6a0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern __arm void func_020ee62c(volatile int *);
extern __arm void func_020edf54(volatile int *);

extern unsigned char data_020da13c[];
extern unsigned char data_020e241c[];

volatile int *func_0208f6a0(volatile int *p)
{
    *p = (unsigned int) data_020e241c;
    *p = (unsigned int) data_020da13c;
    func_020ee62c(p);
    func_020edf54(p);
    return p;
}
