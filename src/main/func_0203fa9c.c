/* func_0203fa9c @ 0x0203fa9c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(void *);

extern unsigned char data_020da13c[];
extern unsigned char data_020dabc0[];

void *func_0203fa9c(void *ptr)
{
    *(volatile void **) ptr = (void *) data_020dabc0;
    *(volatile void **) ptr = (void *) data_020da13c;
    func_020ee62c(ptr);
    return ptr;
}
