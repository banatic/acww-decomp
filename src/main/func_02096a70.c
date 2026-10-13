/* func_02096a70 @ 0x02096a70, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(void *);

extern unsigned char data_020da13c[];
extern unsigned char data_020e2f90[];

void *func_02096a70(void *ptr)
{
    volatile unsigned int *p = (volatile unsigned int *) ptr;
    *p = (unsigned int) data_020e2f90;
    *p = (unsigned int) data_020da13c;
    func_020ee62c(ptr);
    return ptr;
}
