/* func_0208afdc @ 0x0208afdc, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(void *p);

extern unsigned char data_020da13c[];
extern unsigned char data_020e2288[];

void *func_0208afdc(volatile void *obj)
{
    *(volatile unsigned int *) obj = (unsigned int) data_020e2288;
    *(volatile unsigned int *) obj = (unsigned int) data_020da13c;
    func_020ee62c((void *) obj);
    return (void *) obj;
}
