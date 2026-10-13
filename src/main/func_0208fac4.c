/* func_0208fac4 @ 0x0208fac4, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a1f4(void *);
extern void func_0208af00(void *);

extern unsigned char data_020e2400[];

void *func_0208fac4(void *p)
{
    *(unsigned int *) p = (unsigned int) data_020e2400;
    func_0208a1f4((char *) p + 0xC);
    func_0208af00(p);
    return p;
}
