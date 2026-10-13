/* func_0208ae98 @ 0x0208ae98, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020edb3c(void *p);

extern unsigned char data_020da6dc[];
extern unsigned char data_020e2094[];

void *func_0208ae98(volatile unsigned int *p)
{
    *p = (unsigned int) (unsigned int) data_020e2094;
    *p = (unsigned int) (unsigned int) data_020da6dc;
    func_020edb3c((void *) p);
    return (void *) p;
}
