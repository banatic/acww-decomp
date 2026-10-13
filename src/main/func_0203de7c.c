/* func_0203de7c @ 0x0203de7c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(void *ptr);

extern unsigned char data_020da13c[];
extern unsigned char data_020daae4[];

void *func_0203de7c(void *ptr)
{
    *(volatile unsigned int *) ptr = (unsigned int) data_020daae4;
    *(volatile unsigned int *) ptr = (unsigned int) data_020da13c;
    func_020ee62c(ptr);
    return ptr;
}
